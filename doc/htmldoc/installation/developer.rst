.. _dev_install:

Install NEST from source
=========================


This page describes how to build NEST from source in order to *run* it, for example
to tune compiler settings for a specific CPU or to link against a particular MPI
library. If you intend to **contribute** changes back to NEST, start with the
:ref:`git_workflow` instead: it has you create your own fork of the repository first.

.. note::

    Please see our :ref:`development workflows and guidelines <developer_space>`, if you need
    a refresher in git or need to review the coding or documentation guidelines.



* Clone nest-simulator from the central repository on GitHub
  `<https://github.com/nest/nest-simulator>`_:

  .. code-block:: sh

     git clone git@github.com:nest/nest-simulator.git

  This clones the latest development version. To build a specific release
  instead, check out its tag after cloning (see the
  `list of releases <https://github.com/nest/nest-simulator/releases>`_ for
  available versions):

  .. code-block:: sh

     cd nest-simulator
     git checkout v3.10

* or download the tarball for a release `here <https://github.com/nest/nest-simulator/releases>`_ and unpack it:

  .. code-block:: sh

     tar -xzvf nest-simulator-x.y.tar.gz



We have provided an `environment.yml <https://github.com/nest/nest-simulator/blob/main/environment.yml>`_
file that contains all possible packages needed for NEST development.

.. grid:: 3

   .. grid-item-card:: Install NEST with venv
        :link: venv
        :link-type: ref


   .. grid-item-card:: Install NEST with mamba
        :link: condaenv
        :link-type: ref


   .. grid-item-card:: Install NEST without environment
        :link: noenv
        :link-type: ref




.. seealso::

  :ref:`cmake options for NEST <cmake_options>`

What gets installed where
-------------------------

By default, everything will be installed to the subdirectories ``<nest_install_dir>/{bin,lib,share}``, where
``/install/path`` is the install path given to ``cmake``:

- Executables ``<nest_install_dir>/bin``
- Dynamic libraries ``<nest_install_dir>/lib/``
- Examples ``<nest_install_dir>/share/doc/nest/examples``
- PyNEST ``<nest_install_dir>/lib/pythonX.Y/site-packages/nest``
- PyNEST examples ``<nest_install_dir>/share/doc/nest/examples/pynest``

If you want to run the ``nest`` executable or use the ``nest`` Python module without providing explicit paths, you
have to add the installation directory to your search paths.
