.. _synapse_dynamics:

Synapse dynamics
================

The dynamics of synaptic interactions between neurons can be characterized in terms of three distinct factors:

- the postsynaptic response to a single, isolated presynaptic spike,
- the dynamics of synaptic weights (aka synaptic plasticity), as well as
- their across-trial variability  (aka synaptic stochasticity).

This page focuses on the postsynaptic response dynamics. Please visit :ref:`types_synapses` for plasticity and stochasticity in NEST.


Postsynaptic response to a single presynaptic spike
---------------------------------------------------

Voltage dependence
~~~~~~~~~~~~~~~~~~

.. _current_based:

Current-based synapses
^^^^^^^^^^^^^^^^^^^^^^

Current-based synapses model an input current :math:`I_\textrm{syn}(t)` that is
fed as an additive term in the equation for the subthreshold membrane
potential dynamics (:math:`V(t)`) of neurons:

.. math:: \tau_\textrm{m}\frac{dV(t)}{dt}=f(V(t))+\frac{1}{C_\textrm{m}}\,I_\textrm{syn}(t)\,.

The effect of the synaptic input therefore does not depend on the state
(membrane potential) of the neuron. :math:`C_{m}` is the neuronal
capacitance, and the function :math:`f(V(t))` summarizes internal
membrane properties, such as leak potentials.

.. _conductance_based:

Conductance-based synapses
^^^^^^^^^^^^^^^^^^^^^^^^^^

Conductance-based synapses model input currents indirectly via the
dynamics of a conductance :math:`g_{syn}(t)`. This conductance is
multiplied with the distance of the membrane potential :math:`V(t)` from the reversal (Nernst) potential
:math:`V_\mathsf{r}` to yield the current :math:`g_{syn}(t)\,(V(t)-V_{r})`:

.. math:: \tau_\textrm{m}\frac{dV(t)}{dt}=f(V(t))+\frac{1}{C_{m}}\,g_{syn}(t)\,(V(t)-V_{r})\,.

The input therefore has a multiplicative effect that depends on the
state (membrane potential distance from reversal potential
:math:`V_{r}`) of the neuron.

The time dependence of the conductance :math:`g_\textrm{syn}(t)` describes the opening and closing of ion channels.

.. _time_dependence:

Time dependence
~~~~~~~~~~~~~~~

The time dependence of the postsynaptic response to a single presynaptic spike is specified by a kernel :math:`k(t)`.
Synaptic kernels are normalized such that the peak value equals 1.
The kernels differ in shape. The delta kernel describes one pulse only at the time point of the spike arrival.
The exponential kernel models a temporal decay of the post-synaptic response.
Alpha- and beta-function kernels, in addition, account for the finite rise time of the postsynaptic response.


The dynamics in general is given by

.. math::

   \begin{aligned}
   \{I_{syn}(t),g_{syn}(t)\} & \ni x(t)=\sum_{j}w_{j}\,(k\ast s_{j})(t)\end{aligned}

where :math:`\ast` denotes a temporal convolution with presynaptic spike
trains :math:`s_{j}(t)=\sum_{k}\delta(t-t_{j}^{k})` defined by spike
times :math:`t_{j}^{k}`. :math:`w_{j}` denotes the weight of the connection from presynaptic neuron :math:`j`.


.. _delta_synapse:

Delta kernel
^^^^^^^^^^^^


.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2

      .. image:: /static/img/delta_nn.svg

   .. grid-item::
      :columns: 10

      In case synaptic filtering can be neglected, the kernel

      .. math:: k(t)=\delta(t)

      can be regarded as a Dirac delta function.


.. _exp_synapse:

Exponential kernel
^^^^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2

      .. image:: /static/img/exp_nn.svg

   .. grid-item::
      :columns: 10
      :class: sd-d-flex-row sd-align-major-center

      .. tab-set::

       .. tab-item:: General info

          The exponential kernel

          .. math::

            k(t) = \exp(-t/\tau_\mathsf{s})\Theta(t)



          with Heaviside function :math:`\Theta(t)=0` for :math:`t<0` and
          :math:`\Theta(t)=1` for :math:`t\geq0`, and synaptic time constant
          :math:`\tau_{syn}`. The kernel is normalized to have a peak value
          :math:`k(0)=1`\. The kernel corresponds to the
          solution of the ordinary first-order differential equation

          .. math:: \tau_{syn}\frac{dk(t)}{dt}=-k(t)+\tau_{syn}\delta(t)

          with Dirac input at :math:`t=0` and initial condition
          :math:`k(-\infty)=0`.

       .. tab-item:: Technical details

          The synaptic filtering is implemented with an additional state variable
          for the synaptic current or conductance that follows the dynamics:

          .. math:: \tau_{syn}\frac{dk(t)}{dt}=-k(t)+\tau_{syn}\delta(t)

          with spiking input from all presynaptic
          neurons. This dynamics is solved using exact integration (link to exact
          integration page) (ref to Rotter and Diesmann 1999).

.. _alpha_synapse:

Alpha-function kernel
^^^^^^^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2
      :class: sd-d-flex-row sd-align-major-center


      .. image:: /static/img/alpha2.svg

   .. grid-item::
      :columns: 10

      .. tab-set::

       .. tab-item:: General info

          Alpha synapses (alpha) are defined by the filter kernel

          .. math:: k(t)=\frac{e}{\tau_{syn}}t\exp(-t/\tau_{syn})\Theta(t)

          with Euler number :math:`e`, Heaviside function :math:`\Theta(t)=0` for
          :math:`t<0` and :math:`\Theta(t)=1` for :math:`t\geq0`, and synaptic
          time constant :math:`\tau_{syn}`. The kernel is normalized to have a
          peak value :math:`k(\tau_{syn})=1`.
           The kernel corresponds to the solution of the
          system of ordinary differential equations

          .. math::

             \frac{d\kappa(t)}{dt} = - \frac{1}{\tau_\textrm{syn}} \kappa(t) + \frac{e}{\tau_\textrm{syn}} \delta(t) \\
             \frac{d\kappa(t)}{dt} =  - \frac{1}{\tau_\textrm{syn}}k(t) + \kappa(t)

          with Dirac input at :math:`t=0` and initial conditions
          :math:`\kappa(-\infty)=k(-\infty)=0`. The alpha kernel therefore
          represents the consecutive application of two exponential filter
          kernels.

          Note that the above system of differential equations is equivalent to
          the second-order differential equation

          .. math:: \frac{d^{2}k(t)}{dt^{2}}+(a+b)\frac{dk(t)}{dt}+(ab)k(t)=\frac{e}{\tau_{syn}}\,\delta(t)

          with :math:`a=b=1/\tau_{syn}` and initial condition :math:`k(-\infty)=0`
          and :math:`\frac{dk}{dt}(-\infty)=0` (ref Rotter Diesmann 1999). The
          solution to this equation for :math:`a=b` is called alpha function which
          gives rise to the name alpha synapse.


       .. tab-item:: Technical details

          The synaptic filtering is implemented with two additional state
          variables related to the synaptic current or conductance. These
          variables follow the dynamics described in the equations above
          and are solved using exact integration (link to exact
          integration page) (ref to Rotter and Diesmann 1999).


.. _beta_synapse:

Beta-function kernel
^^^^^^^^^^^^^^^^^^^^

.. grid:: 1 2 2 2

   .. grid-item::
      :columns: 2
      :class: sd-d-flex-row sd-align-major-center

      .. image:: /static/img/beta2.svg

   .. grid-item::
      :columns: 10

      .. tab-set::

       .. tab-item:: General info

          Beta synapses are defined by a kernel that is the difference of two
          exponentials.

          The maximum of the beta kernel

          .. math::

            k(t) = \alpha ( \mathsf{exp}(-at) - \mathsf{exp}(-bt)) \Theta(t)

          is at

          .. math::

            t^* = \frac{\mathsf{ln}(a)-\mathsf{ln}(b)}{a-b}

          and not at :math:`t=a` as said in ``iaf_cond_beta``.

          Note that the time constant of the first term in the difference of exponentials
          determines the duration of the decay, not of the rise. If using the subscripts "rise" and "decay",
          then :math:`\tau_\mathsf{rise}=1/b` and :math:`\tau_\mathsf{decay}=1/a`.

          .. math:: k(t)=\frac{\tau_{syn,decay}}{\tau_{syn,rise}-\tau_{syn,decay}}\left[\exp(-t/\tau_{syn,decay})-\exp(-t/\tau_{syn,rise})\right]\Theta(t)

          This function allows for independent rise and decay times, as quantified
          by :math:`\tau_{syn,rise}` and :math:`\tau_{syn,decay}`, respectively.
          The kernel corresponds to the solution of the system of ordinary
          differential equations. The maximum of the kernel is at

          .. math::

            t^* = \frac{\mathsf{ln}\left(\frac{1}{\tau_{syn,decay}}\right)-\mathsf{ln}\left(\frac{1}{\tau_{syn,rise}}\right)}{\frac{1}{\tau_{syn,decay}}-\frac{1}{\tau_{syn,rise}}}


          Alternatively, the system can be written as:

          .. math::

            \kappa' = -a \kappa + \beta \delta(t) \\
            k' = \kappa - b k

          with :math:`\beta = \alpha (b-a)`.

          The system can also be expressed as:

          .. math::

             \begin{aligned}
             \tau_{syn,rise}\frac{dk(t)}{dt} & =-k(t)+\kappa(t)\label{eq:beta1}\\
             \tau_{syn,decay}\frac{d\kappa(t)}{dt} & =-\kappa(t)+\tau_{syn,decay}\delta(t)\label{eq:beta2}\end{aligned}

          with Dirac input at :math:`t=0` and initial conditions
          :math:`\kappa(-\infty)=k(-\infty)=0`. Note that this system of
          differential equations is equivalent to the second-order differential
          equation

          .. math:: \frac{d^{2}k(t)}{dt^{2}}+(a+b)\frac{dk(t)}{dt}+(ab)k(t)=\frac{1}{\tau_{syn,rise}}\delta(t)

          with :math:`a=1/\tau_{syn,rise}\neq b=1/\tau_{syn,decay}` and initial
          condition :math:`k(-\infty)=0` and :math:`\frac{dk}{dt}(-\infty)=0` (ref
          Rotter Diesmann 1999). For the case
          :math:`\tau_{syn,rise}=\tau_{syn,decay}` please use the alpha synapse
          model instead. Even though the limit
          :math:`\tau_{syn,rise}\rightarrow\tau_{syn,decay}` is well defined and
          coincides with the alpha synapse, there can be numerical issues as both
          numerator and denominator in the kernel equation above
          vanish in this limit.


       .. tab-item:: Technical details

          The synaptic filtering is implemented with two additional state
          variables related to the synaptic current or conductance. These
          variables follow the dynamics described in the equations above
          and are solved using exact integration (link to exact
          integration page) (ref to Rotter and Diesmann 1999).



.. Synaptic plasticity

.. Static synapse

.. Short term plasticity

  ?? Long-term potentiation (LTP) and depression (LTD)
  (Do we really have any models of LTP/LTD that do not belong to the category of STDP?)

.. Spike-timing dependent plasticity (STDP)

.. Three-factor plasticity

.. (e.g., clopath*, urbanczik*, eprop*, jonke*, *dopamine*, ...)

.. Structural plasticity
   (We can regard structural plasticity as an extreme case of synaptic-weight dynamics, where weights switch between a finite value and zero.)


.. Synaptic stochasticity

  (e.g., bernoulli_synapse, quantal_stp_synapse)

  Models for synaptic dynamics are distinguished by two different
  features:

  #. whether they describe a current (psc) or conductance (cond)

  #. the temporal response to an incoming spike.





..  Weight dynamics
  ===============

  Above we discussed the postsynaptic dynamics that is elicited after an
  incoming spike with weight :math:`w_{j}`. Next, we study different
  models for how the weight of the connection can change over time.

  Static connections
  ------------------

  Here the weight stays constant over time.

  Synaptic plasticity
  -------------------

  LTP and LTD
  ~~~~~~~~~~~

  STDP
  ~~~~

  Voltage-based plasticity
  ~~~~~~~~~~~~~~~~~~~~~~~~

  Structural plasticity
  ---------------------

  Here the weight of existing connections not only change, but also new
  connections are being formed over time and existing connections are
  being removed.
