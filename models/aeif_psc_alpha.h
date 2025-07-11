/*
 *  aeif_psc_alpha.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AEIF_PSC_ALPHA_H
#define AEIF_PSC_ALPHA_H

// Generated includes:
#include "config.h"

#ifdef HAVE_GSL

// External includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "recordables_map.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"


namespace nest
{
/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 */
extern "C" int aeif_psc_alpha_dynamics( double, const double*, double*, void* );

/* BeginUserDocs: neuron, adaptation, integrate-and-fire, current-based, soft threshold

Short description
+++++++++++++++++

Current-based exponential integrate-and-fire neuron model

Description
+++++++++++

``aeif_psc_alpha`` is the adaptive exponential integrate-and-fire neuron according to Brette and Gerstner (2005).
Synaptic currents are modelled as alpha-functions.

The membrane potential is given by the following differential equation:

.. math::

   C \frac{dV}{dt}= -g_L(V-E_L)+g_L\cdot\Delta_T\cdot\exp((V-V_T)/\Delta_T) - w(t) + I_{syn}(t) + I_e

and

.. math::

   \tau_w \cdot \frac{dw}{dt}= a(V-E_L) - w

.. math::

   I_{syn}(t) = \sum_k (t-t^k) \exp(-(t-t^k)/\tau_{syn})H(t - t^k)

Here :math:`H(t)` is the Heaviside step function and `k` indexes incoming spikes.

**Numerical integration and event handling**

This implementation uses an embedded 4th order Runge-Kutta-Fehlberg solver with adaptive step size (via GSL) to
integrate the system of differential equations for the membrane potential, adaptation variable, and synaptic currents.

**Threshold crossing and spike emission**

- The membrane potential is continuously monitored during ODE integration.
- A spike is emitted immediately when the membrane potential :math:`V_m` reaches or exceeds the spike detection
threshold :math:`V_{\text{peak}}` (or :math:`V_{\text{th}}` if :math:`\Delta_T = 0`), as determined by the ODE solver.
This can occur at any point within a simulation step, not just at the end of a step.
- Upon spike emission:
  - The membrane potential is reset to :math:`V_{\text{reset}}`.
  - The adaptation variable :math:`w` is incremented by the spike-triggered adaptation parameter :math:`b`.
  - The neuron enters a refractory period, during which the membrane potential is clamped to :math:`V_{\text{reset}}`.
  - The refractory period is managed by a counter, and its duration is set by the parameter ``t_ref``. If ``t_ref`` is
zero, the neuron can emit multiple spikes in a single simulation step.

**Refractory period**

- While refractory, the membrane potential is held at :math:`V_{\text{reset}}` and the ODEs are not integrated for
:math:`V_m`.
- The refractory counter is decremented at each simulation step until it reaches zero, after which normal integration
resumes.

**Synaptic and external input**

- Incoming spikes and currents are buffered and applied at the start of each simulation step.
- Synaptic currents are updated according to alpha-function dynamics, and their derivatives are included in the ODE
system.

**Initial conditions and state setting**

- All state variables (membrane potential, adaptation, synaptic currents) can be set via the status dictionary.
- When a spike occurs, the state is updated immediately within the ODE integration loop, not just at the end of a
simulation step.

**Numerical caveats**

- Because the ODE solver uses adaptive step sizes, the exact timing of spikes and resets may not align with the
simulation step boundaries.
- Users should be aware that this can lead to differences in spike timing and adaptation dynamics compared to
event-driven models with fixed time steps.

For further implementation details, see the
`aeif_models_implementation <../model_details/aeif_models_implementation.ipynb>`_ notebook.

.. note::

    The default refractory period for ``aeif`` models is zero, consistent with the model definition in
    Brette & Gerstner [1]_. Thus, an ``aeif`` neuron with default parameters can fire multiple spikes in a single
    time step, which can lead to exploding spike numbers and extreme slow-down of simulations.

    To avoid such unphysiological behavior, you should set a refractory time ``t_ref > 0``.

Parameters
++++++++++

The following parameters can be set in the status dictionary.


**Dynamic state variables**

================== ================== ========================== =================================
**State variable** **Initial value**  **Math equivalent**        **Description**
================== ================== ========================== =================================
``V_m``            -70.6 mV           :math:`V_{\text{m}}`       Membrane potential
``I_ex``           0.0 pA             :math:`I_{\text{syn, ex}}` Excitatory synaptic current
``dI_ex``          0.0 pA/ms          :math:`\frac{dI_{\text{syn, ex}}}{dt}` First derivative of I_ex
``I_in``           0.0 pA             :math:`I_{\text{syn, in}}` Inhibitory synaptic current
``dI_in``          0.0 pA/ms          :math:`\frac{dI_{\text{syn, in}}}{dt}` First derivative of I_in
``w``              0.0 pA             :math:`w`                  Spike-adaptation current
================== ================== ========================== =================================

**Membrane parameters**

=============== ================== ===============================
========================================================================
**Parameter**   **Default**        **Math equivalent**             **Description**
=============== ================== ===============================
========================================================================
``C_m``         281.0 pF           :math:`C_{\text{m}}`            Capacity of the membrane
``t_ref``       0.0 ms             :math:`t_{\text{ref}}`          Duration of refractory period
``V_reset``     -60.0 mV           :math:`V_{\text{reset}}`        Reset value for :math:`V_m` after a spike
``E_L``         -70.6 mV           :math:`E_{\text{L}}`            Leak reversal potential
``g_L``         30.0 nS            :math:`g_{\text{L}}`            Leak conductance
``I_e``         0.0 pA             :math:`I_{\text{e}}`            Constant external input current
=============== ================== ===============================
========================================================================

**Spike adaptation parameters**

=============== ================== ===============================
========================================================================
**Parameter**   **Default**        **Math equivalent**             **Description**
=============== ================== ===============================
========================================================================
``a``           4.0 nS             :math:`a`                        Subthreshold adaptation
``b``           80.5 pA            :math:`b`                        Spike-triggered adaptation
``Delta_T``     2.0 mV             :math:`\Delta_T`                 Slope factor
``tau_w``       144.0 ms           :math:`\tau_w`                   Adaptation time constant
``V_th``        -50.4 mV           :math:`V_{\text{th}}`            Spike initiation threshold
``V_peak``      0.0 mV             :math:`V_{\text{peak}}`          Spike detection threshold
=============== ================== ===============================
========================================================================

**Synaptic parameters**

=============== ================== ===============================
========================================================================
**Parameter**   **Default**        **Math equivalent**             **Description**
=============== ================== ===============================
========================================================================
``tau_syn_ex``  0.2 ms             :math:`\tau_{\text{syn, ex}}`    Rise time of excitatory synaptic conductance (alpha
function)
``tau_syn_in``  2.0 ms             :math:`\tau_{\text{syn, in}}`    Rise time of inhibitory synaptic conductance (alpha
function)
=============== ================== ===============================
========================================================================


Sends
+++++

SpikeEvent

Receives
++++++++

SpikeEvent, CurrentEvent, DataLoggingRequest

References
++++++++++

.. [1] Brette R and Gerstner W (2005). Adaptive Exponential
       Integrate-and-Fire Model as an Effective Description of Neuronal
       Activity. J Neurophysiol 94:3637-3642.
       DOI: https://doi.org/10.1152/jn.00686.2005

See also
++++++++

iaf_psc_alpha, aeif_cond_exp

Examples using this model
+++++++++++++++++++++++++

.. listexamples:: aeif_psc_alpha

EndUserDocs */

void register_aeif_psc_alpha( const std::string& name );

class aeif_psc_alpha : public ArchivingNode
{

public:
  aeif_psc_alpha();
  aeif_psc_alpha( const aeif_psc_alpha& );
  ~aeif_psc_alpha() override;

  /**
   * Import sets of overloaded virtual functions.
   * @see Technical Issues / Virtual Functions: Overriding, Overloading, and
   * Hiding
   */
  using Node::handle;
  using Node::handles_test_event;

  size_t send_test_event( Node&, size_t, synindex, bool ) override;

  void handle( SpikeEvent& ) override;
  void handle( CurrentEvent& ) override;
  void handle( DataLoggingRequest& ) override;

  size_t handles_test_event( SpikeEvent&, size_t ) override;
  size_t handles_test_event( CurrentEvent&, size_t ) override;
  size_t handles_test_event( DataLoggingRequest&, size_t ) override;

  void get_status( DictionaryDatum& ) const override;
  void set_status( const DictionaryDatum& ) override;

private:
  void init_buffers_() override;
  void pre_run_hook() override;
  void update( Time const&, const long, const long ) override;

  // END Boilerplate function declarations ----------------------------

  // Friends --------------------------------------------------------

  // make dynamics function quasi-member
  friend int aeif_psc_alpha_dynamics( double, const double*, double*, void* );

  // The next two classes need to be friends to access the State_ class/member
  friend class RecordablesMap< aeif_psc_alpha >;
  friend class UniversalDataLogger< aeif_psc_alpha >;

private:
  // ----------------------------------------------------------------

  //! Independent parameters
  struct Parameters_
  {
    double V_peak_;  //!< Spike detection threshold in mV
    double V_reset_; //!< Reset Potential in mV
    double t_ref_;   //!< Refractory period in ms

    double g_L;        //!< Leak Conductance in nS
    double C_m;        //!< Membrane Capacitance in pF
    double E_L;        //!< Leak reversal Potential (aka resting potential) in mV
    double Delta_T;    //!< Slope factor in mV
    double tau_w;      //!< Adaptation time-constant in ms
    double a;          //!< Subthreshold adaptation in nS
    double b;          //!< Spike-triggered adaptation in pA
    double V_th;       //!< Spike threshold in mV
    double tau_syn_ex; //!< Excitatory synaptic rise time
    double tau_syn_in; //!< Excitatory synaptic rise time
    double I_e;        //!< Intrinsic current in pA

    double gsl_error_tol; //!< Error bound for GSL integrator

    Parameters_(); //!< Sets default parameter values

    void get( DictionaryDatum& ) const;             //!< Store current values in dictionary
    void set( const DictionaryDatum&, Node* node ); //!< Set values from dictionary
  };

public:
  // ----------------------------------------------------------------

  /**
   * State variables of the model.
   * @note Copy constructor required because of C-style array.
   */
  struct State_
  {
    /**
     * Enumeration identifying elements in state array State_::y_.
     * The state vector must be passed to GSL as a C array. This enum
     * identifies the elements of the vector. It must be public to be
     * accessible from the iteration function.
     */
    enum StateVecElems
    {
      V_M = 0,
      DI_EXC, // 1
      I_EXC,  // 2
      DI_INH, // 3
      I_INH,  // 4
      W,      // 5
      STATE_VEC_SIZE
    };

    double y_[ STATE_VEC_SIZE ]; //!< neuron state, must be C-array for
                                 //!< GSL solver
    unsigned int r_;             //!< number of refractory steps remaining

    State_( const Parameters_& ); //!< Default initialization
    State_( const State_& );

    State_& operator=( const State_& );

    void get( DictionaryDatum& ) const;
    void set( const DictionaryDatum&, const Parameters_&, Node* );
  };

  // ----------------------------------------------------------------

  /**
   * Buffers of the model.
   */
  struct Buffers_
  {
    Buffers_( aeif_psc_alpha& );                  //!< Sets buffer pointers to 0
    Buffers_( const Buffers_&, aeif_psc_alpha& ); //!< Sets buffer pointers to 0

    //! Logger for all analog data
    UniversalDataLogger< aeif_psc_alpha > logger_;

    /** buffers and sums up incoming spikes/currents */
    RingBuffer spike_exc_;
    RingBuffer spike_inh_;
    RingBuffer currents_;

    /** GSL ODE stuff */
    gsl_odeiv_step* s_;    //!< stepping function
    gsl_odeiv_control* c_; //!< adaptive stepsize control function
    gsl_odeiv_evolve* e_;  //!< evolution function
    gsl_odeiv_system sys_; //!< struct describing the GSL system

    // Since IntegrationStep_ is initialized with step_, and the resolution
    // cannot change after nodes have been created, it is safe to place both
    // here.
    double step_;            //!< step size in ms
    double IntegrationStep_; //!< current integration time step, updated by GSL

    /**
     * Input current injected by CurrentEvent.
     * This variable is used to transport the current applied into the
     * _dynamics function computing the derivative of the state vector.
     * It must be a part of Buffers_, since it is initialized once before
     * the first simulation, but not modified before later Simulate calls.
     */
    double I_stim_;
  };

  // ----------------------------------------------------------------

  /**
   * Internal variables of the model.
   */
  struct Variables_
  {
    /** initial value to normalise excitatory synaptic current */
    double i0_ex_;

    /** initial value to normalise inhibitory synaptic current */
    double i0_in_;

    /**
     * Threshold detection for spike events: P.V_peak if Delta_T > 0.,
     * P.V_th if Delta_T == 0.
     */
    double V_peak;

    unsigned int refractory_counts_;
  };

  // Access functions for UniversalDataLogger -------------------------------

  //! Read out state vector elements, used by UniversalDataLogger
  template < State_::StateVecElems elem >
  double
  get_y_elem_() const
  {
    return S_.y_[ elem ];
  }

  // ----------------------------------------------------------------

  Parameters_ P_;
  State_ S_;
  Variables_ V_;
  Buffers_ B_;

  //! Mapping of recordables names to access functions
  static RecordablesMap< aeif_psc_alpha > recordablesMap_;
};

inline size_t
aeif_psc_alpha::send_test_event( Node& target, size_t receptor_type, synindex, bool )
{
  SpikeEvent e;
  e.set_sender( *this );

  return target.handles_test_event( e, receptor_type );
}

inline size_t
aeif_psc_alpha::handles_test_event( SpikeEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
aeif_psc_alpha::handles_test_event( CurrentEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
aeif_psc_alpha::handles_test_event( DataLoggingRequest& dlr, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
}

inline void
aeif_psc_alpha::get_status( DictionaryDatum& d ) const
{
  P_.get( d );
  S_.get( d );
  ArchivingNode::get_status( d );

  ( *d )[ names::recordables ] = recordablesMap_.get_list();
}

inline void
aeif_psc_alpha::set_status( const DictionaryDatum& d )
{
  Parameters_ ptmp = P_;     // temporary copy in case of errors
  ptmp.set( d, this );       // throws if BadProperty
  State_ stmp = S_;          // temporary copy in case of errors
  stmp.set( d, ptmp, this ); // throws if BadProperty

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  ArchivingNode::set_status( d );

  // if we get here, temporaries contain consistent set of properties
  P_ = ptmp;
  S_ = stmp;
}

} // namespace

#endif // HAVE_GSL
#endif // AEIF_PSC_ALPHA_H
