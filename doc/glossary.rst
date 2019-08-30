Glossary
==============

.. glossary::

 SLI
    simulation language interface of NEST, a stack language

 PyNESTML
     the python-based modeling language of NEST

 Topology
    a module in NEST to construct structured networks in 2D and 3D

Parameters in NEST
-------------------

Connections in NEST
~~~~~~~~~~~~~~~~~~~~~~

See :doc:`guides/connection_management` for our guide on managing connections in NEST.

.. glossary::

 pre
   source neurons

 post
   target neurons

 conn_spec
    specifies connection rules

 syn_spec
    the synapse type and its properties

 autapses
     An autapse is a synapse (connection) from a node onto itself. Autapses are permitted by default, but can be
     disabled by adding ``allow_autapses: False`` to the  connection dictionary.

 multapses
     Node A is connected to node B by a multapse if there are synapses (connections) from A to
     B. Multapses are permitted by default, but can be disabled by adding ``allow_multapses: False`` to the connection dictionary.
     autapses

 one_to_one
     connection rule where the `ith` node in :term:`pre` is connected to the `ith` node in :term:`post`

 fixed_indegree
    The nodes in :term:`pre` are randomly connected with the nodes in :term:`post`
    such that each node in :term:`post` has a fixed number of incoming connections.

 fixed_outdegree
    The nodes in :term:`pre` are randomly connected with the nodes in :term:`post`
    such that each node in :term:`pre` has a fixed number of outgoing connections.

 all_to_all
     connection rule where each node in :term:`pre` is connected to all nodes in :term:`post`
     default rule for connections

 fixed_total_number
    The nodes in :term:`pre` are randomly connected with the nodes in :term:`post`
    such that the total number of connections equals ``N``.

 pairwise_bernoulli
    For each possible pair of nodes from :term:`pre` and :term:`post`, a connection
    is created with probability ``p``.

 weight
     strength of synapse (connection between neurons)

 delay
      time interval for synaptic signal to reach target

 receptor_type
     target connection type on post-synaptic neuron; exact meaning depends on which model is used (see :doc:`models/index`).
     Use command ``GetDefaults("synapse_model")`` to see default values.

 rdevdict
    dictionary of available distribution parameters of synapses

 resolution
     the step interval that each neuron is updated at during simulation



MPI related commands
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. glossary::


 NumProcesses
     The number of MPI processes in the simulation

 ProcessorName
     The name of the machine. The result might differ on each process.

 Rank
     The rank of the MPI process. The result differs on each process.

 SyncProcesses
      Synchronize all MPI processes.


Common abbreviations in NEST
------------------------------
.. glossary::

 iaf
   integrate and fire

 dat
   file extensions of analog recordings from the multimeter

 gdf
   file extension of spike files

 gif
   generalized integrate and fire

 cond
   conductance-based

 psc
   post synaptic current (current-based)

 hh
   Hodgkin Huxley

 rng
   random number generator

 wfr
   waveform relaxation method

 aeif
   adaptive exponential integrate and fire

 ht
   Hill and Tononi

 pp
   point process

 in
   inhibitory

 ex
   excitatory

 MAM
   multi-area model

 mpi
   message passing interface

 stdp
   spike-timing dependent plasticity synapse

 st
   short term plasticity

 vp
   virtual process

Physical units in NEST
--------------------------


.. glossary::

 **time**
    milliseconds `ms`

 tau_m
    Membrane time constant in ms

 t_ref
    Duration of refractory period in ms

 t_spike
    point in time of last spike in

 **capacitance**
    picofarads `pF`

 C_m
    Capacitance of the membrane in pF

 **current**
    picoamperes `pA`

 I_e
    Constant input current in pA.

 **conductance**
    nanosiemens `nS`

 g_L
    Leak conductance in nS

 g_K
    Potassium peak conductance in nS.

 g_Na
    Sodium peak conductance in nS.

 **spike rates**
    spikes/s

 **modulation frequencies**
    herz `Hz`

 frequency
    frequncy in Hz

 **voltage**
   millivolts `mV`

 V_m
   Membrane potential in mV

 E_L
   Resting membrane potential in mV.

 V_th
   Spike threshold in mV.

 V_reset double
   Reset potential of the membrane in mV.

 V_min
   Absolute lower value for the membrane potential in mV

 E_ex
   Excitatory reversal potential in mV.

 E_in
    Inhibitory reversal potential in mV.

 E_Na
   Sodium reversal potential in mV.

 E_K
   Potassium reversal potential in mV.


Terminlogy for toplogy module
------------------------------

You can find more information regarding topology including tutorial and comprehensive user guide :doc:`here <topology/index>`

.. glossary::


 Connection
    In the context of connections between the elements of Topology layers, we often call the set of all connections
    between pairs of network nodes created by a single call to
    ``ConnectLayers`` a connection

 Connection dictionary
    A dictionary specifying the properties of a connection between two layers in a call to
    ``CreateLayers``.

 Source
    The source of a single connection is the node sending signals (usually spikes). In a projection, the
    source layer is the layer from which source nodes are chosen.

 Target
    The target of a single connection is the node receiving signals (usually spikes). In a projection, the
    target layertarget layer is the layer from which target nodes are chosen.

 Connection type
    Connection type determines how nodes are selected when ``ConnectLayers`` creates connections between layers. It is
    either ``convergent! or ``divergent!.

 Convergent connection
    When creating a convergent connection between layers, Topology visits each node in the target layer in turn and selects sources for
    it in the source layer. Masks and kernels are applied to the source layer, and periodic boundary conditions are applied in the source
    layer, provided that the source layer has periodic boundary conditions.

 Divergent connection
    When creating a divergent connection, Topology visits each node in the source layer and selects target nodes from the target layer. Masks, kernels, and
    boundary conditions are applied in the target layer.

 Driver
    When connecting two layers, the driver layer is the one in which each node is considered in
    turn.

 Pool
    When connecting two layers, the pool layer is the one from which nodes are chosen for each
    node in the driver layer. I.e., we have

    +----------------+--------------+--------------+
    |Connection type |  Driver      | Pool         |
    +================+==============+==============+
    |convergent      | target layer | source layer |
    +----------------+--------------+--------------+
    |divergent       | source layer | target layer |
    +----------------+--------------+--------------+

 Displacement
    The displacement between a driver and a pool node is the shortest vector connecting
    the driver to the pool node, taking boundary conditions into account.

 Distance
    The distance between a driver and a pool node is the length of their displacement.

 Mask
    The mask defines which pool nodes are at all considered as potential targets for each driver node.

 Kernel
    The kernel is a function returning a (possibly distance- or displacement-dependent)
    probability for creating a connection between a driver and a pool node. The default kernel is $1$, i.e., connections are created with
    certainty.


