.. _neurons_index:

All about neurons in NEST
=========================


.. grid:: 1 1 3 3
   :gutter: 1

   .. grid-item-card::
       :class-header: sd-d-flex-row sd-align-minor-center sd-bg-info sd-text-white


       |neuron|  Neuron types in NEST
       ^^^


       * :ref:`types_neurons`: Find out about the various neuron models and their mechanisms that are available in NEST

       * :ref:`neuron_update`: Learn how NEST handles the steps to update the dynamics of neurons during simulation.


   .. grid-item-card::
       :class-header: sd-d-flex-row sd-align-minor-center sd-bg-info sd-text-white


       |python| Using neurons in PyNEST scripts
       ^^^

       * :ref:`Manipulating nodes (neurons and devices) <node_handles>`: understand basic functionality of nodes
       * :ref:`param_ex`: explore how to use parameter objects in NEST


   .. grid-item-card::
       :class-header: sd-d-flex-row sd-align-minor-center sd-bg-info sd-text-white


       |math| Find a specific model
       ^^^


       For details on individual models, please take alook at our model directory, where you can
       select various tags and refine the results to your choosing, or look up our A-Z list.

       * :doc:`/models/index`



----

.. |nav| image:: /static/img/GPS-Settings-256_nest.svg
.. |script| image:: /static/img/script_white.svg
      :scale: 20%
.. |start| image:: /static/img/start_white.svg
      :scale: 40%
.. |user| image:: /static/img/020-user.svg
.. |teacher| image:: /static/img/014-teacher.svg
.. |admin| image:: /static/img/001-shuttle.svg
.. |dev| image:: /static/img/dev_orange.svg
.. |nestml| image:: /static/img/nestml-logo.png
      :scale: 15%
.. |synapse| image:: /static/img/synapse_white.svg
.. |neuron|  image:: /static/img/neuron_white.svg
.. |glossary|  image:: /static/img/glossary_white.svg
.. |git|  image:: /static/img/git_white.svg
.. |refresh|  image:: /static/img/refresh_white.svg
.. |hpc|  image:: /static/img/hpc_white.svg
.. |random|  image:: /static/img/random_white.svg
.. |math|  image:: /static/img/math_white.svg
.. |network|  image:: /static/img/network_brain_white.svg
.. |device|  image:: /static/img/device_white.svg
.. |connect|  image:: /static/img/connect_white.svg
.. |sonata|  image:: /static/img/sonata_white.svg
.. |write|  image:: /static/img/write_nest_white.svg
      :scale: 60%
.. |parallel| image:: /static/img/parallel_white.svg
.. |simulate| image:: /static/img/simulate_white.svg
.. |interactive| image:: /static/img/interactive_white.svg
.. |python| image:: /static/img/python_white.svg
.. |gallery| image:: /static/img/gallery_white.svg


.. toctree::
   :hidden:

   neuron_types
   parametrization
   node_handles
   exact-integration
   simulations_with_precise_spike_times
