.. _types_synapses:

Types of synapses
=================


.. grid::
   :gutter: 1

   .. grid-item-card::
     :columns: 3
     :class-item: sd-text-center
     :link: chemical_synapses
     :link-type: ref


     .. image:: /static/img/synapse_chemical1.svg

   .. grid-item-card::
     :columns: 3
     :class-item: sd-text-center
     :link:  electrical_synapses
     :link-type: ref


     .. image:: /static/img/synapse_electrical.svg

    .. grid-item-card::
      :columns: 3
      :class-item: sd-text-center
      :link: astrocytic_coupling
      :link-type: ref


      .. image:: /static/img/synapse_astrocyte_title.svg

    .. grid-item-card::
      :columns: 3
      :class-item: sd-text-center
      :link: rate_synapses
      :link-type: ref


      .. image:: /static/img/synapse_abstract_title1.svg


.. grid::
   :gutter: 1

   .. grid-item::
     :columns: 12

      In the following section, we introduce the different types of synapse model implemented in NEST. This page focuses on the
      type of signal transmission and plasticity for each synapse model. For details on the post-synaptic response
      dynamics of synapses, see :ref:`synapse_dynamics`. Some synapse models require specific neuron types, which is indicated
      in the model description. While various synapse types can theoretically be combined, implementation limitations exist
      in NEST. For custom synapse models, consider using NESTML.

.. _chemical_synapses:

Chemical synapses
-----------------

The majority of synapse models in NEST implement chemical synapses.


- **Signal transmission type:** Unidirectional spike transmission from pre-synaptic to post-synaptic neuron
- **Weight and delay:** Characterized by a (plastic) weight and (static) delay

  - **Synaptic weight:** Various mechanisms can change the synaptic weight over time, see `Types of plasticity` below.
  - **Delay:** Represents electrochemical signal conversion and signal propagation from synapse to postsynaptic soma.

    In NEST, delays are considerd fully dendritic, with one exception: ``stdp_pl_synapse_hom_ax_delay``. This synapse
    model supports ``axonal_delay`` and ``dendtritic_delay`` parameters. For more information,
    see :doc:`Delays` and :doc:`Example using axonal delay` >>>> **PR 2989!**

Types of plasticity
~~~~~~~~~~~~~~~~~~~

Static synapses
^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2
      :class: sd-d-flex-row sd-align-major-center

      .. image:: /static/img/synapse_static_t2.svg

   .. grid-item::
      :columns: 10

      .. tab-set::

        .. tab-item:: General info
          :selected:

          Connection does not change over time.


            .. dropdown:: Static synapses

               - static_synapse - chemical, static
               - static_synapse_hom_w - chemical, static


Functional plasticity
^^^^^^^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2
      :class: sd-d-flex-row sd-align-major-center

      .. image:: /static/img/synapse_functional_t2.svg

   .. grid-item::
      :columns: 10

      .. tab-set::

        .. tab-item:: General info
          :selected:

          Connection weight changes over time.

        .. tab-item:: **STP**

           .. grid::
             :gutter: 1

             .. grid-item::
               :columns: 4

               .. image:: /static/img/synapse_stp_notitle.svg

             .. grid-item::
               :columns: 8

               - Short-term plasticity (STP)

               - Depends only on presynaptic neuron spiking activity

               - Can exhibit either facilitation (increased response) or depression (decreased response)

               .. dropdown:: STP synapse models

                    {% for items in tag_dict %}
                    {% if items.tag == "stp" %}
                    {% for item in items.models | sort %}
                    * :doc:`/models/{{ item | replace(".html", "") }}`
                    {% endfor %}
                    {% endif %}
                    {% endfor %}

        .. tab-item:: **STDP**

           .. grid::
              :gutter: 1

              .. grid-item::
                :columns: 4

                 .. image:: /static/img/synapse_stdp_notitle.svg

              .. grid-item::
                :columns: 8

                - Spike timing dependent plasticity (STDP)

                - Depends on the relative timing of pre- and post-synaptic spikes

                - The effect can be either additive or multiplicative, depending on the specific implementation

                - Different window functions determine the temporal dependence of plasticity

                .. dropdown:: STDP synapse models

                       {% for items in tag_dict %}
                       {% if items.tag == "stdp" %}
                       {% for item in items.models | sort %}
                       * :doc:`/models/{{ item | replace(".html", "") }}`
                       {% endfor %}
                       {% endif %}
                       {% endfor %}

        .. tab-item:: **3 factor rules**

          .. grid::
            :gutter: 1

            .. grid-item::
               :columns: 4

               .. image:: /static/img/synapse_stdp_3rd_notitle.svg

            .. grid-item::
               :columns: 8

               - Spike timing dependent plasticity and STDP-like models with third factors

               - The third factor modulates the effectiveness of synaptic weight changes

               - This third factor can be a neuromodulation signal or a local signal from the postsynaptic neuron, such as membrane potential or dendritic voltage


               .. dropdown:: Synapse models with 3rd factors

                  {% for items in tag_dict %}
                  {% if items.tag == "static" %}
                  {% for item in items.models | sort %}
                  * :doc:`/models/{{ item | replace(".html", "") }}`
                  {% endfor %}
                  {% endif %}
                  {% endfor %}


Structural plasticity
^^^^^^^^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2
      :class: sd-d-flex-row sd-align-major-center

      .. image:: /static/img/synapse_structural_t2.svg


   .. grid-item::
      :columns: 10

      .. tab-set::

        .. tab-item:: General info
          :selected:

          Synapses are dynamically created or deleted.

          :doc:`Example using structural plasticity in NEST <auto_examples/structural_plasticity>`


Stochasticity
~~~~~~~~~~~~~

Spike transmission in chemical synapses is not always reliable due to diffusion of neurotransmitters and stochastic
neurotransmitter release. Most synapse models in NEST use deterministic signal transmission; however,
the ``bernoulli_synapse`` implements stochastic spike transmission.

* bernoulli_synapse - chemical, static, stochastic

.. _electrical_synapses:


Electrical Synapses
-------------------

.. tab-set::

  .. tab-item:: General info
    :selected:

    **Signal transmission type:** Voltage

    Electrical synapses provide direct electrical coupling between the membranes of two neurons, resulting
    in instantaneous signal transmission. The strength of coupling is determined by the conductance. Unlike chemical
    synapses, signal transmission is bidirectional. These synapses are typically considered static and deterministic.

  .. tab-item:: Technical details

    - Instantaneous coupling requires waveform relaxation (WFR)
    - This is enabled by default (``use_wfr = True``)
    - Most users don't need to change any settings
    - For advanced configuration options, see the :doc:`/synapses/simulations_with_gap_junctions` documentation

Available models: gap_junction - electrical

.. _astrocytic_coupling:

Astrocytic coupling
-------------------

**Signal transmission type:** Current

Astrocytic coupling modulates neuronal activity by producing slow inward currents to neurons, which in turn are affected by
neuronal activity. This creates a recurrent interaction between astrocytes and neurons.

**Available models:**

- sic_connection - astrocyte

.. _rate_synapses:

Rate neurons
------------

**Signal transmission type:** Firing rates

Rate neurons transmit continuous signals representing firing rates between neurons.

.. tab-set::

  .. tab-item:: General info
    :selected:

    Rate neurons are used with rate-based neuron models for efficient population-level simulations.

  .. tab-item:: Technical details

    - Rate connections with delay buffer information during the minimum delay period and send it as a packet
    - Other connections submit single values instantaneously

**Available models:**

- cont_delay_synapse - abstract, rate
- diffusion_connection - abstract, rate
- erate_connection_delayed - abstract, rate
- rate_connection_instantaneous - abstract, rate

.. _auxiliary_synapses:

Auxiliary synapses
-----------------

.. tab-set::

  .. tab-item:: General info
    :selected:

    **Signal transmission type:** Learning signals and other continuous signals

    Auxiliary synapses are models without direct biological counterparts, typically used with
    complex plasticity models requiring learning signals between neurons (e.g., e-prop). They typically submit arrays
    of continuous signals.

  .. tab-item:: Technical details

    - Connections submit single values instantaneously

**Available models:**

- eprop_learning_signal_connection - abstract, learning
- eprop_learning_signal_connection_bsshslm_2020 - abstract, learning
- eprop_synapse - abstract, learning
- prop_synapse_bsshslm_2020 - abstract, learning

----

* clopath_synapse - chemical, functional, stdp, 3-factor
* ht_synapse - chemical, functional, stp
* jonke_synapse - chemical, functional, stdp, 3-factor
* quantal_stp_synapse - chemical, functional, stp
* stdp_dopamine_synapse - chemical, functional, stdp, 3-factor
* stdp_facetshw_synapse_hom - chemical, functional, stdp
* stdp_nn_pre_centered_synapse - chemical, functional, stdp
* stdp_nn_restr_synapse - chemical, functional, stdp
* stdp_nn_symm_synapse - chemical, functional, stdp
* stdp_pl_synapse_hom - chemical, functional, stdp
* stdp_synapse - chemical, functional, stdp
* stdp_synapse_hom - chemical, functional, stdp
* stdp_triplet_synapse - chemical, functional, stdp
* tsodyks2_synapse - chemical, functional, stp
* tsodyks_synapse - chemical, functional, stp
* tsodyks_synapse_hom - chemical, functional, stp
* urbanczik_synapse - chemical, functional, stdp, 3-factor
* vogels_sprekeler_synapse - chemical, functional, stdp, 3-factor
