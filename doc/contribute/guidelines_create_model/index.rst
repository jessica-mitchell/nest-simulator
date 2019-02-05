Create your own model in NEST
===============================

.. sidebar:: NAVIGATION

   * :ref:`naming_conventions`
   * :ref:`update_models`
   * :doc:`../guidelines_docs/index`
   * :doc:`NEST developer space <../../developer_space/index>`

The NEST simulator is a scientific tool that is is constantly changing
to meet the needs of novel neuroscientific endeavors. If the functionality
you need is not included in NEST already, **you can extend NEST**. The
easiest way to add neuron or synapse models to NEST is in the form of a
plugin in the form of an extension module:

-  :doc:`Writing an Extension Module <extension_modules>`

.. note::

   To create models more efficiently, **the NEST modeling language (NESTML)** is currently
   under development.
   It is a domain-specific language that supports the specification of neuron models
   in a precise and concise syntax, based on the syntax of Python.
   Several of the neuron models in NEST are already
   available in the repository. **Check out** https://github.com/nest/nestml

A **neuron model** in NEST is a C++ class that contains the neuron dynamics
and implements the API for setting and retrieving parameters, updating
the dynamics, sending and receiving events, and recording analog
quantities from the model.

**Devices** are similar to neurons, but used to stimulate the network or
record from the neurons without necessarily having internal dynamics:

-  :doc:`Developing neuron and device models <neuron_and_device_models>`
-  :doc:`Multimeter support for models <multimeter_support>`

**Synapses** mediate the signal flow between neuron or device models. They
can either be static or implement synaptic plasticity rules such as
`spike time dependent plasticity
(STDP) <http://www.scholarpedia.org/article/Spike-timing_dependent_plasticity>`__:

-  :doc:`Synapses in NEST: An overview <synapses_overview>`
-  :doc:`Developing synapse models <synapse_models>`

.. _naming_conventions:

Naming Conventions
--------------------

To ensure consistency, NEST must adhere to **coding and naming conventions**. Please ensure
you follow these guidelines while adding new features to NEST:

* :doc:`naming_conventions/neuron_model_naming`
* :doc:`naming_conventions/synapse_model_naming`
* :doc:`naming_conventions/variables_parameters_naming`

.. _update_models:

Updating models to 2.16
-----------------------

With the introduction of the new connection infrastructure of the `5g
kernel <https://www.frontiersin.org/articles/10.3389/fninf.2018.00002/full>`__,
rate neuron, synapse, and device models need to be slightly adapted from
prior versions to be compatible with the latest release (2.16). In the
following we describe all necessary changes:

-  :doc:`How to update models from NEST 2.14 or prior to
   2.16 <update_model/model_conversion_5g>`

Updating models to 2.6 or later
-------------------------------

If you find models written for NEST version 2.4 and prior not working
anymore in newer versions, it is most likely due to recent updates to
the API for neuron and synapse models. We’ve put together a conversion
guide to make the transition of models easier for you:

-  `How to update models from NEST 2.4 or prior to 2.6 or
   later <model_conversion_3g_4g>`__

Want to dig deeper?
--------------------

We encourage all kinds of contributions to NEST! Check out our :doc:`Developer Space <../../developer_space/index>`
for our code development and maintenance guidelines.


