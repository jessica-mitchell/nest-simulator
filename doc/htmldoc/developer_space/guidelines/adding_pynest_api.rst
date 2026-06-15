.. _pyapi_guide:

Add or modify the PyNEST API
============================

This guide explains how the PyNEST Python interface is layered, where your code
belongs, and the conventions to follow. It ends with a copy-paste template for a
new high-level function.

The four layers
---------------

A call such as ``nest.Create("iaf_psc_alpha", 10)`` travels through four layers::

    user script
        │   nest.Create(...)
        ▼
  ┌─────────────────────────────────────────────┐
  │ 1. Module assembly      nest/__init__.py    │  builds the `nest` namespace
  ├─────────────────────────────────────────────┤
  │ 2. High-level API       nest/lib/hl_api*.py │  ◀── you almost always work here
  ├─────────────────────────────────────────────┤
  │ 3. Cython boundary      nestkernel_api.pyx  │  llapi_* glue to C++
  │                         nestkernel_api.pxd  │  C++ declarations
  ├─────────────────────────────────────────────┤
  │ 4. C++ kernel           nestkernel/*.cpp    │
  └─────────────────────────────────────────────┘

1. Module assembly — ``nest/__init__.py``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You rarely touch this. The ``nest`` module is not a normal module: it is replaced
at import time by a ``NestModule`` instance. Public names from each ``hl_api_*``
module are pulled into ``nest`` namespace by ``_rel_import_star``, which
copies exactly the names listed in that module's ``__all__``.

The practical consequences for you:

- **A new module** (``hl_api_foo.py``) only becomes visible after you add a
  ``_rel_import_star(self, ".lib.hl_api_foo")`` line in ``NestModule.__init__``.
- **A new function in an existing module** becomes visible the moment you add it
  to that module's ``__all__``. Nothing else is required.
- Kernel status fields (e.g. ``nest.resolution``) are *not* functions; they are
  ``KernelAttribute`` descriptors declared in ``NestModule``. See
  :ref:`Kernel attributes <pynest_kernel_attr>` below.

2. High-level API — ``nest/lib/hl_api_*.py``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is where user-facing functions live, grouped by topic. Pick the module that
matches your feature:

================================  ===========================================
Module                            Responsibility
================================  ===========================================
``hl_api_nodes.py``               ``Create``, node lookup
``hl_api_connections.py``         ``Connect``, ``Disconnect``, connection queries
``hl_api_connection_helpers.py``  internal helpers for ``Connect``
``hl_api_simulation.py``          ``Simulate``, ``Run``, kernel status
``hl_api_models.py``              model / copy / defaults
``hl_api_info.py``                help, ``GetStatus`` / ``SetStatus``
``hl_api_types.py``               ``NodeCollection``, ``SynapseCollection``, ``Parameter``, ``Mask``
``hl_api_parallel_computing.py``  ``Rank``, ``NumProcesses``, MPI
``hl_api_spatial.py``             spatially structured networks
``hl_api_sonata.py``              SONATA network import
``hl_api_helper.py``              shared, non-public utilities + decorators
================================  ===========================================

3. Cython boundary — ``nestkernel_api.pyx`` / ``.pxd``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Only edit these if you need to reach a C++ function that is **not yet exposed**.
The pattern is consistent:

- ``nestkernel_api.pxd`` declares the C++ signature, e.g.

  .. code-block:: cython

      NodeCollectionPTR create(const string& model_name, const long n) except +custom_exception_handler

  The ``except +custom_exception_handler`` clause turns C++ exceptions into
  Python ``NESTError``\ s — always include it.

- ``nestkernel_api.pyx`` defines a thin ``llapi_*`` wrapper that converts Python
  objects to C++ types and wraps results back into PyNEST objects:

  .. code-block:: cython

      def llapi_create(model, long n):
          cdef NodeCollectionPTR gids
          gids = create(pystr_to_string(model), n)
          obj = NodeCollectionObject()
          obj._set_nc(gids)
          return nest.NodeCollection(obj)

Keep ``llapi_*`` functions dumb: type conversion only, **no user-facing logic, no
validation messages, no docstrings**. All of that belongs in layer 2. Editing
these files requires recompiling NEST.

Conventions for high-level functions
------------------------------------

- **License header.** Every ``.py`` file starts with the standard GPL header
   block (copy it from any existing ``hl_api_*.py``). The second comment line
   must be the file name.

- **Export via** ``__all__``. Only names in ``__all__`` reach the ``nest.``
   namespace. Keep the list alphabetically sorted. Helpers that should stay
   private are simply left out of ``__all__`` (or prefixed with ``_``).

- **NumPy-style docstrings**, parsed by Sphinx / ``numpydoc``. Use the
   ``Parameters`` / ``Returns`` / ``Raises`` sections, and cross-reference other
   API with ``:py:func:`.Connect``` or ``:py:class:`.NodeCollection```. The first
   line is a one-sentence imperative summary.

- **Nodes are** ``NodeCollection``\ **s.** Any function that returns node IDs
   returns a ``NodeCollection``; any function that accepts nodes accepts one.
   Never expose raw integer IDs (see ``lib/README.md``).

- **Validate in Python, fail early.** Check argument types and raise
   ``TypeError`` / ``ValueError`` with a clear message *before* calling into the
   kernel, as ``Create`` does. Kernel-side errors surface as ``nest.NESTError``.

- **Deprecate, don't delete.** Use the ``@deprecated`` decorator from
   ``hl_api_helper`` to phase out a function, and ``model_deprecation_warning``
   for models. This keeps user scripts working across releases.

- **Naming.** User-facing API functions are ``CamelCase`` (``Create``,
   ``Connect``, ``GetStatus``); internal helpers are ``snake_case``.

.. _pynest_kernel_attr:

Kernel attributes (status fields)
---------------------------------

If you are exposing a new *scalar kernel setting* (something read or written via
the kernel status dict, like ``nest.resolution``), you do **not** write a
function. Add a ``KernelAttribute`` descriptor in ``NestModule`` in
``nest/__init__.py``:

.. code-block:: python

    my_setting = KernelAttribute(
        "float",                              # type hint shown in docs
        "One-line description, no trailing period",
        default=1.0,                          # omit if no default
        readonly=False,                       # True for computed/read-only values
    )

The descriptor automatically dispatches to ``llapi_get_kernel_status`` /
``llapi_set_kernel_status``. Mind the formatting notes in that file: no trailing
punctuation, and split multi-line strings with ``+`` concatenation.

Template for a new high-level function
--------------------------------------

.. code-block:: python

    # -*- coding: utf-8 -*-
    #
    # hl_api_<topic>.py
    #
    # This file is part of NEST.
    #
    # ... (full GPL header — copy verbatim from a neighbouring hl_api_*.py) ...

    """
    Functions for <topic>
    """

    from .. import nestkernel_api as nestkernel
    from .hl_api_helper import deprecated
    from .hl_api_types import NodeCollection

    __all__ = [
        "MyFunction",
    ]


    def MyFunction(nodes, value=1.0):
        """One-line imperative summary of what this does.

        Optional longer description giving context, caveats, and how the
        function relates to the rest of the API such as :py:func:`.Create`.

        Parameters
        ----------
        nodes : NodeCollection
            The nodes to operate on.
        value : float, optional
            What this controls and its default behaviour.

        Returns
        -------
        NodeCollection
            Description of the returned object.

        Raises
        ------
        TypeError
            If ``nodes`` is not a NodeCollection.
        """

        # 1. Validate in Python and fail early with a clear message.
        if not isinstance(nodes, NodeCollection):
            raise TypeError("MyFunction requires a NodeCollection")

        # 2. Delegate the real work to the kernel through a thin llapi_* call.
        result = nestkernel.llapi_my_function(nodes._datum, value)

        # 3. Wrap/return results following API conventions (NodeCollection, etc.).
        return result

To make ``MyFunction`` reachable as ``nest.MyFunction``:

- it is already in ``__all__`` above; **and**
- if ``hl_api_<topic>.py`` is a *new* file, add
  ``_rel_import_star(self, ".lib.hl_api_<topic>")`` to ``NestModule.__init__`` in
  ``nest/__init__.py``.

Before you open a PR
--------------------

- Function added to ``__all__`` (and module wired in ``__init__.py`` if new).
- NumPy-style docstring with ``Parameters`` / ``Returns`` / ``Raises``.
- Inputs validated in Python; kernel reached only through ``llapi_*``.
- Tests added under ``testsuite/pytests/`` (mirror an existing ``test_*.py``).
- ``import nest; help(nest.MyFunction)`` shows your docstring cleanly.

.. note::

  Documentation should automatically be built for new or modified functions and modules.
  https://nest-simulator.readthedocs.io/en/stable/ref_material/pynest_api/index.html

  You can check this when you create a PR. A Read the Docs build will automatically
  start in CI on GitHub for your PR. You can view it in the `Conversation` tab, where the checks are run.
