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
     :link: astrocyte_synapses
     :link-type: ref


     .. image:: /static/img/synapse_astrocyte_title.svg

   .. grid-item-card::
     :columns: 3
     :class-item: sd-text-center
     :link: abstract_synapses
     :link-type: ref


     .. image:: /static/img/synapse_abstract_title1.svg


.. grid::
   :gutter: 1

   .. grid-item::
     :columns: 12

     In the following section, we introduce the different types of synapses implemented in NEST. This page focuses on the
     type of signal transmission and plasticity for each synapse model. For details on the post-synaptic response
     dynamics of synapses, see :ref:`synapse_dynamics`.

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

          - Connection does not change over time


            .. dropdown:: Static synapses

               - static_synapse - chemical, static
               - static_synapse_hom_w - chemical, static

        .. tab-item:: Technical details

          * empty

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

          - Connection weight changes over time

          - Spike timing dependent plasticity (STDP)
          - Short-term plasticity (STP)
          - Models with three factors

        .. tab-item:: **STDP**

          .. grid::
             :gutter: 1

             .. grid-item::
               :columns: 4

                .. image:: /static/img/synapse_stdp_notitle.svg

             .. grid-item::
               :columns: 8

               - Spike timing dependent plasticity (STDP)
               - Depends on the relative timing of pre- and post-synaptic spikes. The effect can be either additive or
                 multiplicative, depending on the specific implementation. Different window functions determine the
                 temporal dependence of plasticity. The time scale is typically on the order of a few milliseconds.

               .. dropdown:: STDP synapses

                      {% for items in tag_dict %}
                      {% if items.tag == "stdp" %}
                      {% for item in items.models | sort %}
                      * :doc:`/models/{{ item | replace(".html", "") }}`
                      {% endfor %}
                      {% endif %}
                      {% endfor %}

        .. tab-item:: **STP**

           .. grid::
             :gutter: 1

             .. grid-item::
               :columns: 4

               .. image:: /static/img/synapse_stp_notitle.svg

             .. grid-item::
               :columns: 8

               - Short-term plasticity (STP)

               - Depends on presynaptic neuron spiking activity. Can exhibit either facilitation (increased response) or
                 depression (decreased response). The time scale is typically tens of milliseconds.

               .. dropdown:: STP synapses

                    {% for items in tag_dict %}
                    {% if items.tag == "stp" %}
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
               - The third factor modulates the effectiveness of synaptic weight changes. This third factor can be a
                 neuromodulation signal or a local signal from the postsynaptic neuron, such as membrane potential or
                 dendritic voltage. The time scale is similar to standard STDP (a few milliseconds).


               .. dropdown:: Synapses with 3rd factors

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

          - Synapses are dynamically created or deleted
          - NEST does not have any models that specifically support structural plasticity.

            .. dropdown:: Synapses with structural plasticity

               {% for items in tag_dict %}
               {% if items.tag == "structural" %}
               {% for item in items.models | sort %}
               * :doc:`/models/{{ item | replace(".html", "") }}`
               {% endfor %}
               {% endif %}
               {% endfor %}

        .. tab-item:: Technical details

          * empty

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

    Electrical synapses provide direct electrical coupling between pre- and post-synaptic neuron membranes, resulting
    in instantaneous signal transmission. The strength of coupling is determined by the conductance. Unlike chemical
    synapses, signal transmission is bidirectional. These synapses are typically considered static and deterministic.

  .. tab-item:: Technical details

    - Instantaneous coupling requires waveform relaxation

Available models: gap_junction - electrical

Astrocytes
----------

**Signal transmission type:** Current

Astrocytes modulate neuronal activity by producing slow inward currents to neurons, which in turn are affected by
neuronal activity. This creates a bidirectional interaction between astrocytes and neurons.

**Available models:**
- sic_connection - astrocyte

.. _abstract_synapses:

Abstract Synapses
-----------------

.. tab-set::

  .. tab-item:: General info
    :selected:

    **Signal transmission type:** Firing rates, learning signals, and other continuous signals

    Abstract synapses represent all synapses that do not fit into the other categories. These are auxiliary
    models without direct biological counterparts, typically used with abstract neuron models like rate models or
    complex plasticity models requiring learning signals between neurons (e.g., e-prop). They typically submit arrays
    of continuous signals.

  .. tab-item:: Technical details

    - Rate connections with delay buffer information during the minimum delay period and send it as a packet
    - Other connections submit single values instantaneously

**Available models:**

- cont_delay_synapse - abstract, rate
- diffusion_connection - abstract, rate
- eprop_learning_signal_connection - abstract, learning
- eprop_learning_signal_connection_bsshslm_2020 - abstract, learning
- eprop_synapse - abstract, learning
- erate_connection_delayed - abstract, rate
- rate_connection_instantaneous - abstract, rate
- prop_synapse_bsshslm_2020 - abstract, learning
- weight_optimizer

.. _astrocyte_synapses:


----

* clopath_synapse - chemical, functional, stdp+3rd
* ht_synapse -
* jonke_synapse - chemical, functional, stdp+3rd
* quantal_stp_synapse - chemical, functional, stp
* stdp_dopamine_synapse - chemical, functional, stdp+3rd
* stdp_facetshw_synapse_hom - chemical, functional, stdp
* stdp_nn_pre_centered_synapse- chemical, functional, stdp
* stdp_nn_restr_synapse- chemical, functional, stdp
* stdp_nn_symm_synapse- chemical, functional, stdp
* stdp_pl_synapse_hom- chemical, functional, stdp
* stdp_synapse- chemical, functional, stdp
* stdp_synapse_hom- chemical, functional, stdp
* stdp_triplet_synapse- chemical, functional, stdp
* tsodyks2_synapse - chemical, functional, stp
* tsodyks_synapse- chemical, functional, stp
* tsodyks_synapse_hom- chemical, functional, stp
* urbanczik_synapse- chemical, functional, stdp+3rd
* vogels_sprekeler_synapse - chemical, functional, stdp+3rd
