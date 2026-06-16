/*
 *  iaf_chxk_2008.h
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

#ifndef IAF_CHXK_2008_H
#define IAF_CHXK_2008_H

// Generated includes:
#include "config.h"

#ifdef HAVE_GSL

// C includes:
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

// Disable clang-formatting for documentation due to over-wide tables.
// clang-format off
/* BeginUserDocs: neuron, integrate-and-fire, conductance-based, precise, hard threshold

Short description
+++++++++++++++++

Conductance-based leaky integrate-and-fire neuron model supporting
precise spike times used in Casti et al. 2008

Description
+++++++++++

``iaf_chxk_2008`` is a conductance-based leaky integrate-and-fire neuron model [1]_ with

* a hard threshold,
* no explicit reset and no explicit refractory period,
* spike-triggered afterhyperpolarization (AHP) instead of a reset,
* :math:`\alpha`-shaped synaptic and AHP conductances, as in ``iaf_cond_alpha``,
* precise spike times.

Membrane potential evolution and spike emission
...............................................

The membrane potential evolves according to

.. math::

   C_{\text{m}} \frac{dV_\text{m}}{dt} = -g_{\text{L}} (V_\text{m} - E_{\text{L}})
   - g_{\text{ex}}(t) (V_\text{m} - E_{\text{ex}})
   - g_{\text{in}}(t) (V_\text{m} - E_{\text{in}})
   - g_{\text{ahp}}(t) (V_\text{m} - E_{\text{ahp}}) + I_\text{e}

A spike is emitted when :math:`V_\text{m}` crosses the threshold :math:`V_\text{th}` from below. The
membrane potential is not reset explicitly; instead, the spike activates an afterhyperpolarizing
(AHP) conductance :math:`g_{\text{ahp}}` that repolarizes the neuron over time.

Synaptic and AHP input
......................

The excitatory and inhibitory synaptic conductances and the AHP conductance follow
:math:`\alpha`-function time courses, as in the ``iaf_cond_alpha`` model. The synaptic conductances
are normalized such that an event of weight 1.0 results in a peak conductance of 1 nS, while the AHP
conductance is triggered with peak :math:`g_{\text{ahp}}` on each spike.

.. note::
   In accordance with the original Fortran implementation of the model used
   in [1]_, the activation time point for the AHP following a spike is
   determined by linear interpolation within the time step during which the
   threshold was crossed.

   ``iaf_chxk_2008`` neurons therefore emit spikes with precise spike time
   information, but they ignore precise spike times when handling synaptic
   input.

.. note::
   In the original Fortran implementation underlying [1]_, all previous AHP
   activation was discarded when a new spike occurred, leading to reduced AHP
   currents in particular during periods of high spiking activity. Set
   ``ahp_bug`` to ``true`` to obtain this behavior in the model.

Parameters
++++++++++

The following parameters can be set in the status dictionary.

============== =========== ============================= ===================================================================
**Parameter**  **Default** **Math equivalent**           **Description**
============== =========== ============================= ===================================================================
``E_L``        -60 mV      :math:`E_\text{L}`            Leak reversal potential
``C_m``        1000 pF     :math:`C_{\text{m}}`          Capacity of the membrane
``V_th``       -45 mV      :math:`V_{\text{th}}`         Spike threshold
``E_ex``       20 mV       :math:`E_\text{ex}`           Excitatory reversal potential
``E_in``       -90 mV      :math:`E_\text{in}`           Inhibitory reversal potential
``g_L``        100 nS      :math:`g_\text{L}`            Leak conductance
``tau_syn_ex`` 1 ms        :math:`\tau_{\text{syn, ex}}` Rise time of the excitatory synaptic alpha function
``tau_syn_in`` 1 ms        :math:`\tau_{\text{syn, in}}` Rise time of the inhibitory synaptic alpha function
``tau_ahp``    0.5 ms      :math:`\tau_{\text{ahp}}`     Afterhyperpolarization (AHP) time constant
``E_ahp``      -95 mV      :math:`E_{\text{ahp}}`        AHP reversal potential
``g_ahp``      443.8 nS    :math:`g_{\text{ahp}}`        AHP peak conductance
``I_e``        0 pA        :math:`I_\text{e}`            Constant input current
``ahp_bug``    False                                     If ``True``, reproduce the AHP reset of the original implementation
============== =========== ============================= ===================================================================

The following state variables evolve during simulation and are available either as neuron properties or as recordables.

================== ================= ========================== ==================================
**State variable** **Initial value** **Math equivalent**        **Description**
================== ================= ========================== ==================================
``V_m``            -60 mV            :math:`V_{\text{m}}`       Membrane potential
``g_ex``           0 nS              :math:`g_{\text{ex}}`      Excitatory synaptic conductance
``g_in``           0 nS              :math:`g_{\text{in}}`      Inhibitory synaptic conductance
``g_ahp``          0 nS              :math:`g_{\text{ahp}}`     Afterhyperpolarization conductance
``I_syn_ex``       0 pA              :math:`I_{\text{syn, ex}}` Excitatory synaptic input current
``I_syn_in``       0 pA              :math:`I_{\text{syn, in}}` Inhibitory synaptic input current
``I_ahp``          0 pA              :math:`I_{\text{ahp}}`     Afterhyperpolarization current
================== ================= ========================== ==================================

References
++++++++++

.. [1] Casti A, Hayot F, Xiao Y, Kaplan E (2008) A simple model of retina-LGN
       transmission. Journal of Computational Neuroscience 24:235-252.
       DOI: https://doi.org/10.1007/s10827-007-0053-7

Sends
+++++

SpikeEvent

Receives
++++++++

SpikeEvent, CurrentEvent

See also
++++++++

iaf_cond_alpha

Examples using this model
+++++++++++++++++++++++++

.. listexamples:: iaf_chxk_2008

EndUserDocs */
// clang-format on

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
extern "C" int iaf_chxk_2008_dynamics( double, const double*, double*, void* );

void register_iaf_chxk_2008( const std::string& name );

class iaf_chxk_2008 : public ArchivingNode
{

  // Boilerplate function declarations --------------------------------

public:
  iaf_chxk_2008();
  iaf_chxk_2008( const iaf_chxk_2008& );
  ~iaf_chxk_2008() override;

  /**
   * Import sets of overloaded virtual functions.
   * @see Technical Issues / Virtual Functions: Overriding, Overloading, and
   * Hiding
   */
  using Node::handle;
  using Node::handles_test_event;

  size_t send_test_event( Node&, size_t, synindex, bool ) override;

  bool
  is_off_grid() const override
  {
    return true;
  }

  size_t handles_test_event( SpikeEvent&, size_t ) override;
  size_t handles_test_event( CurrentEvent&, size_t ) override;
  size_t handles_test_event( DataLoggingRequest&, size_t ) override;

  void handle( SpikeEvent& ) override;
  void handle( CurrentEvent& ) override;
  void handle( DataLoggingRequest& ) override;

  void get_status( Dictionary& ) const override;
  void set_status( const Dictionary& ) override;

private:
  void init_buffers_() override;
  void pre_run_hook() override;
  void update( Time const&, const long, const long ) override;

  // END Boilerplate function declarations ----------------------------

  // Friends --------------------------------------------------------

  // make dynamics function quasi-member
  friend int iaf_chxk_2008_dynamics( double, const double*, double*, void* );

  // The next two classes need to be friends to access the State_ class/member
  friend class RecordablesMap< iaf_chxk_2008 >;
  friend class UniversalDataLogger< iaf_chxk_2008 >;

private:
  // Parameters class -------------------------------------------------

  //! Model parameters
  struct Parameters_
  {
    double V_th;      //!< Threshold Potential in mV
    double g_L;       //!< Leak Conductance in nS
    double C_m;       //!< Membrane Capacitance in pF
    double E_ex;      //!< Excitatory reversal Potential in mV
    double E_in;      //!< Inhibitory reversal Potential in mV
    double E_L;       //!< Leak reversal Potential (a.k.a. resting potential) in mV
    double tau_synE;  //!< Synaptic Time Constant Excitatory Synapse in ms
    double tau_synI;  //!< Synaptic Time Constant for Inhibitory Synapse in ms
    double I_e;       //!< Constant Current in pA
    double tau_ahp;   //!< Afterhyperpolarization (AHP) time constant
    double g_ahp;     //!< AHP conductance
    double E_ahp;     //!< AHP potential
    bool ahp_bug;     //!< If true, discard AHP conductance value from previous
                      //!< spikes

    Parameters_();  //!< Set default parameter values

    void get( Dictionary& ) const;              //!< Store current values in Dictionary
    void set( const Dictionary&, Node* node );  //!< Set values from Dictionary
  };

  // State variables class --------------------------------------------

  /**
   * State variables of the model.
   *
   * State variables consist of the state vector for the subthreshold
   * dynamics and the refractory count. The state vector must be a
   * C-style array to be compatible with GSL ODE solvers.
   *
   * @note Copy constructor required because  of the C-style array.
   */
public:
  struct State_
  {
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      V_M = 0,
      DG_EXC,
      G_EXC,
      DG_INH,
      G_INH,
      DG_AHP,
      G_AHP,
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double y[ STATE_VEC_SIZE ];

    //!< number of refractory steps remaining
    int r;

    State_( const Parameters_& );  //!< Default initialization
    State_( const State_& );

    State_& operator=( const State_& );

    void get( Dictionary& ) const;  //!< Store current values in Dictionary

    /**
     * Set state from values in Dictionary.
     * Requires Parameters_ as argument to, e.g., check bounds.'
     */
    void set( const Dictionary&, const Parameters_&, Node* );
  };

private:
  // Buffers class --------------------------------------------------------

  /**
   * Buffers of the model.
   * Buffers are on par with state variables in terms of persistence,
   * i.e., initialized only upon first Simulate call after ResetKernel, but are
   * implementation details hidden from the user.
   */
  struct Buffers_
  {
    Buffers_( iaf_chxk_2008& );                   //!< Sets buffer pointers to 0
    Buffers_( const Buffers_&, iaf_chxk_2008& );  //!< Sets buffer pointers to 0

    //! Logger for all analog data
    UniversalDataLogger< iaf_chxk_2008 > logger_;

    /** buffers and sums up incoming spikes/currents */
    RingBuffer spike_exc_;
    RingBuffer spike_inh_;
    RingBuffer currents_;

    /* GSL ODE stuff */
    gsl_odeiv_step* s_;     //!< stepping function
    gsl_odeiv_control* c_;  //!< adaptive step size control function
    gsl_odeiv_evolve* e_;   //!< evolution function
    gsl_odeiv_system sys_;  //!< struct describing system

    // Since IntegrationStep_ is initialized with step_, and the resolution
    // cannot change after nodes have been created, it is safe to place both
    // here.
    double step_;             //!< step size in ms
    double IntegrationStep_;  //!< current integration time step, updated by GSL

    /**
     * Input current injected by CurrentEvent.
     * This variable is used to transport the current applied into the
     * _dynamics function computing the derivative of the state vector.
     * It must be a part of Buffers_, since it is initialized once before
     * the first simulation, but not modified before later Simulate calls.
     */
    double I_stim_;
  };

  // Variables class -------------------------------------------------------

  /**
   * Internal variables of the model.
   * Variables are re-initialized upon each call to Simulate.
   */
  struct Variables_
  {
    /**
     * Impulse to add to DG_EXC on spike arrival to evoke unit-amplitude
     * conductance excursion.
     */
    double PSConInit_E;

    /**
     * Impulse to add to DG_INH on spike arrival to evoke unit-amplitude
     * conductance excursion.
     */
    double PSConInit_I;

    /**
     * Impulse to add to DG_AHP on spike generation to evoke unit-amplitude
     * conductance excursion.
     */
    double PSConInit_AHP;
  };

  // Access functions for UniversalDataLogger -------------------------------

  //! Read out state vector elements, used by UniversalDataLogger
  template < State_::StateVecElems elem >
  double
  get_y_elem_() const
  {
    return S_.y[ elem ];
  }

  //! Read out remaining refractory time, used by UniversalDataLogger
  double
  get_r_() const
  {
    return Time::get_resolution().get_ms() * S_.r;
  }

  double
  get_I_syn_exc_() const
  {
    return S_.y[ State_::G_EXC ] * ( S_.y[ State_::V_M ] - P_.E_ex );
  }
  double
  get_I_syn_inh_() const
  {
    return S_.y[ State_::G_INH ] * ( S_.y[ State_::V_M ] - P_.E_in );
  }
  double
  get_I_ahp_() const
  {
    return S_.y[ State_::G_AHP ] * ( S_.y[ State_::V_M ] - P_.E_ahp );
  }


  // Data members -----------------------------------------------------------

  // keep the order of these lines, seems to give best performance
  Parameters_ P_;
  State_ S_;
  Variables_ V_;
  Buffers_ B_;

  //! Mapping of recordables names to access functions
  static RecordablesMap< iaf_chxk_2008 > recordablesMap_;
};


// Boilerplate inline function definitions ----------------------------------

inline size_t
iaf_chxk_2008::send_test_event( Node& target, size_t receptor_type, synindex, bool )
{
  SpikeEvent e;
  e.set_sender( *this );

  return target.handles_test_event( e, receptor_type );
}

inline size_t
iaf_chxk_2008::handles_test_event( SpikeEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_chxk_2008::handles_test_event( CurrentEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_chxk_2008::handles_test_event( DataLoggingRequest& dlr, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
}

inline void
iaf_chxk_2008::get_status( Dictionary& d ) const
{
  P_.get( d );
  S_.get( d );
  ArchivingNode::get_status( d );

  d[ names::recordables ] = recordablesMap_.get_list();
}

inline void
iaf_chxk_2008::set_status( const Dictionary& d )
{
  Parameters_ ptmp = P_;      // temporary copy in case of errors
  ptmp.set( d, this );        // throws if BadProperty
  State_ stmp = S_;           // temporary copy in case of errors
  stmp.set( d, ptmp, this );  // throws if BadProperty

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  ArchivingNode::set_status( d );

  // if we get here, temporaries contain consistent set of properties
  P_ = ptmp;
  S_ = stmp;
}

}  // namespace


#endif  // HAVE_GSL
#endif  // IAF_CHXK_2008_H
