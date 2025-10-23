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
     :link: abstract_synapses
     :link-type: ref


     .. image:: /static/img/synapse_abstract_title1.svg


   .. grid-item-card::
     :columns: 3
     :class-item: sd-text-center
     :link: astrocyte_synapses
     :link-type: ref


     .. image:: /static/img/synapse_astrocyte_title.svg

.. grid::
   :gutter: 1

   .. grid-item::
     :columns: 12

     In the following section, we introduce the different types of synapses implemented in NEST. This page focuses on the
     type of signal transmission and plasticity for each synapse model. For details on the dynamics of synapses
     see :ref:`synapse_dynamics`.

.. _chemical_synapses:

Chemical synapses
-----------------

- transmitted signal type: spike
- only chemical synapses have plasticity


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

          - Connection changes over time

          - Spike timing dependent plasticity
          - Short-term plasticity
          - Spike timing dependent plascticity and stdp-like models with 3rd factors

        .. tab-item:: **STDP**

          .. grid::
             :gutter: 1

             .. grid-item::
               :columns: 4

                .. image:: /static/img/synapse_stdp_notitle.svg

             .. grid-item::
               :columns: 8

               Spike timing dependent plascticity

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

               Short-term plasticity


               .. dropdown:: STP synapses

                    {% for items in tag_dict %}
                    {% if items.tag == "stp" %}
                    {% for item in items.models | sort %}
                    * :doc:`/models/{{ item | replace(".html", "") }}`
                    {% endfor %}
                    {% endif %}
                    {% endfor %}

        .. tab-item:: **STDP (-like) + 3rd factor**

          .. grid::
            :gutter: 1

            .. grid-item::
               :columns: 4

               .. image:: /static/img/synapse_stdp_3rd_notitle.svg

            .. grid-item::
               :columns: 8

               Spike timing dependent plasticity and STDP-like models with 3rd factors

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

Stochastic vs Deterministic synapses
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* bernoulli_synapse - chemical, static, stochastic

.. _electrical_synapses:


Electrical Synapses
-------------------

transmitted signal type: voltage

* gap_junction - electrical

.. _abstract_synapses:

Abstract Synapses
-----------------

transmitted signal type: [firing rates, learning signals . . .]


* cont_delay_synapse - abstract, rate
* diffusion_connection - abstract, rate
* eprop_learning_signal_connection - abstract, learning
* eprop_learning_signal_connection_bsshslm_2020 - abstract, learning
* eprop_synapse - abstract, learning
* erate_connection_delayed - abstract, rate
* rate_connection_instantaneous - abstract, rate
* prop_synapse_bsshslm_2020 - abstract, learning
* weight_optimizer

.. _astrocyte_synapses:

Astrocytes
----------

transmitted signal type: current

sic_connection - astrocyte

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
