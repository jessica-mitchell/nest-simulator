/*
 *  iaf_psc_exp_htum.h
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


#ifndef iaf_psc_exp_htum_H
#define iaf_psc_exp_htum_H

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

namespace nest
{

// Disable clang-formatting for documentation due to over-wide tables.
// clang-format off
/* BeginUserDocs: neuron, integrate-and-fire, current-based, hard threshold

Short description
+++++++++++++++++

Leaky integrate-and-fire model with separate relative and absolute refractory period

Description
+++++++++++

``iaf_psc_exp_htum`` is a leaky integrate-and-fire neuron model with

* a hard threshold,
* separate absolute and total refractory periods, as required by [1]_,
* no adaptation mechanisms,
* exponentially-shaped synaptic input currents (infinitely short rise time).

Membrane potential evolution and spike emission
...............................................

The membrane potential evolves according to

.. math::

   \frac{dV_\text{m}}{dt} = -\frac{V_{\text{m}} - E_\text{L}}{\tau_{\text{m}}} + \frac{I_{\text{syn}} + I_\text{e}}{C_{\text{m}}}

where the synaptic input current :math:`I_{\text{syn}}(t)` is discussed below and :math:`I_\text{e}` is
a constant input current set as a model parameter. A spike is emitted when :math:`V_\text{m}` reaches
the threshold :math:`V_\text{th}`, after which it is reset to :math:`V_{\text{reset}}`.

Refractoriness
..............

The threshold crossing is followed by an absolute refractory period :math:`t_{\text{ref, abs}}`
during which the membrane potential is clamped to :math:`V_{\text{reset}}`. During the total
refractory period :math:`t_{\text{ref, tot}}`, the membrane potential evolves, but the neuron does
not emit a spike even if :math:`V_\text{m}` reaches threshold. The total refractory time must be
larger than or equal to the absolute refractory time; if they are equal, the refractoriness is
equivalent to the other integrate-and-fire models of NEST.

Synaptic input
..............

The synaptic input current has an excitatory and an inhibitory component,
:math:`I_{\text{syn}}(t) = I_{\text{syn, ex}}(t) + I_{\text{syn, in}}(t)`, where the individual
post-synaptic currents (PSCs) decay exponentially,

.. math::

   i_{\text{syn, X}}(t) = e^{-\frac{t}{\tau_{\text{syn, X}}}} \Theta(t) \;,

with :math:`\Theta(x)` the Heaviside step function.

The linear subthreshold dynamics is integrated by the Exact
Integration scheme [2]_. The neuron dynamics is solved on the time
grid given by the computation step size. Incoming as well as emitted
spikes are forced to that grid.

An additional state variable and the corresponding differential
equation represents a piecewise constant external current.

The general framework for the consistent formulation of systems with
neuron like dynamics interacting by point events is described in
[2]_. A flow chart can be found in [3]_.

.. note::

   The present implementation uses individual variables for the
   components of the state vector and the non-zero matrix elements of
   the propagator. Because the propagator is a lower triangular matrix,
   no full matrix multiplication needs to be carried out and the
   computation can be done "in place", i.e. no temporary state vector
   object is required.

   The template support of recent C++ compilers enables a more succinct
   formulation without loss of runtime performance already at minimal
   optimization levels. A future version of iaf_psc_exp_htum will probably
   address the problem of efficient usage of appropriate vector and
   matrix objects.

.. note::

   If ``tau_m`` is very close to ``tau_syn_ex`` or ``tau_syn_in``, the model
   will numerically behave as if ``tau_m`` is equal to ``tau_syn_ex`` or
   ``tau_syn_in``, respectively, to avoid numerical instabilities.

    For implementation details see the
    `IAF Integration Singularity notebook <../model_details/IAF_Integration_Singularity.ipynb>`_.


See also [4]_.

Parameters
++++++++++

The following parameters can be set in the status dictionary.

============== =========== ============================= ====================================================
**Parameter**  **Default** **Math equivalent**           **Description**
============== =========== ============================= ====================================================
``E_L``        -70 mV      :math:`E_\text{L}`            Resting membrane potential
``C_m``        250 pF      :math:`C_{\text{m}}`          Capacity of the membrane
``tau_m``      10 ms       :math:`\tau_{\text{m}}`       Membrane time constant
``tau_syn_ex`` 2 ms        :math:`\tau_{\text{syn, ex}}` Time constant of excitatory synaptic current
``tau_syn_in`` 2 ms        :math:`\tau_{\text{syn, in}}` Time constant of inhibitory synaptic current
``t_ref_abs``  2 ms        :math:`t_{\text{ref, abs}}`   Duration of absolute refractory period (V_m clamped)
``t_ref_tot``  2 ms        :math:`t_{\text{ref, tot}}`   Duration of total refractory period (no spiking)
``V_th``       -55 mV      :math:`V_{\text{th}}`         Spike threshold
``V_reset``    -70 mV      :math:`V_{\text{reset}}`      Reset potential of the membrane
``I_e``        0 pA        :math:`I_\text{e}`            Constant input current
============== =========== ============================= ====================================================

The following state variables evolve during simulation and are available either as neuron properties or as recordables.

================== ================= ========================== =================================
**State variable** **Initial value** **Math equivalent**        **Description**
================== ================= ========================== =================================
``V_m``            -70 mV            :math:`V_{\text{m}}`       Membrane potential
``I_syn_ex``       0 pA              :math:`I_{\text{syn, ex}}` Excitatory synaptic input current
``I_syn_in``       0 pA              :math:`I_{\text{syn, in}}` Inhibitory synaptic input current
================== ================= ========================== =================================

References
++++++++++

.. [1] Tsodyks M, Uziel A, Markram H (2000). Synchrony generation in recurrent
       networks with frequency-dependent synapses. The Journal of Neuroscience,
       20,RC50:1-5. URL: https://infoscience.epfl.ch/record/183402
.. [2] Hill, A. V. (1936). Excitation and accommodation in nerve. Proceedings of
       the Royal Society of London. Series B-Biological Sciences, 119(814), 305-355.
       DOI: https://doi.org/10.1098/rspb.1936.0012
.. [3] Rotter S,  Diesmann M (1999). Exact simulation of
       time-invariant linear systems with applications to neuronal
       modeling. Biologial Cybernetics 81:381-402.
       DOI: https://doi.org/10.1007/s004220050570
.. [4] Diesmann M, Gewaltig M-O, Rotter S, & Aertsen A (2001). State
       space analysis of synchronous spiking in cortical neural
       networks. Neurocomputing 38-40:565-571.
       DOI: https://doi.org/10.1016/S0925-2312(01)00409-X

Sends
+++++

SpikeEvent

Receives
++++++++

SpikeEvent, CurrentEvent, DataLoggingRequest

Examples using this model
+++++++++++++++++++++++++

.. listexamples:: iaf_psc_exp_htum

EndUserDocs */
// clang-format on

void register_iaf_psc_exp_htum( const std::string& name );

class iaf_psc_exp_htum : public ArchivingNode
{

public:
  iaf_psc_exp_htum();
  iaf_psc_exp_htum( const iaf_psc_exp_htum& );

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

  void get_status( Dictionary& ) const override;
  void set_status( const Dictionary& ) override;

private:
  void init_buffers_() override;
  void pre_run_hook() override;

  void update( Time const&, const long, const long ) override;

  // The next two classes need to be friends to access the State_ class/member
  friend class RecordablesMap< iaf_psc_exp_htum >;
  friend class UniversalDataLogger< iaf_psc_exp_htum >;

  // ----------------------------------------------------------------

  /**
   * Independent parameters of the model.
   */
  struct Parameters_
  {
    /** Membrane time constant in ms. */
    double Tau_;

    /** Membrane capacitance in pF. */
    double C_;

    /** Refractory period in ms. */
    double tau_ref_tot_;
    double tau_ref_abs_;

    /** Resting potential in mV. */
    double E_L_;

    /** External current in pA */
    double I_e_;

    /** Threshold, RELATIVE TO RESTING POTENTIAL(!).
        I.e. the real threshold is (E_L_+Theta_). */
    double Theta_;

    /** reset value of the membrane potential */
    double V_reset_;

    /** Time constant of excitatory synaptic current in ms. */
    double tau_ex_;

    /** Time constant of inhibitory synaptic current in ms. */
    double tau_in_;

    Parameters_();  //!< Sets default parameter values

    void get( Dictionary& ) const;  //!< Store current values in dictionary

    /** Set values from dictionary.
     * @returns Change in reversal potential E_L, to be passed to State_::set()
     */
    double set( const Dictionary&, Node* node );
  };

  // ----------------------------------------------------------------

  /**
   * State variables of the model.
   */
  struct State_
  {
    // state variables
    double i_0_;       //!< synaptic dc input current, variable 0
    double i_syn_ex_;  //!< postsynaptic current for exc. inputs, variable 1
    double i_syn_in_;  //!< postsynaptic current for inh. inputs, variable 1
    double V_m_;       //!< membrane potential, variable 2

    //! absolute refractory counter (no membrane potential propagation)
    int r_abs_;
    int r_tot_;  //!< total refractory counter (no spikes can be generated)

    State_();  //!< Default initialization

    void get( Dictionary&, const Parameters_& ) const;

    /** Set values from dictionary.
     * @param dictionary to take data from
     * @param current parameters
     * @param Change in reversal potential E_L specified by this dict
     */
    void set( const Dictionary&, const Parameters_&, double delta_EL, Node* );
  };

  // ----------------------------------------------------------------

  /**
   * Buffers of the model.
   */
  struct Buffers_
  {
    Buffers_( iaf_psc_exp_htum& );
    Buffers_( const Buffers_&, iaf_psc_exp_htum& );

    /** buffers and sums up incoming spikes/currents */
    RingBuffer spikes_ex_;
    RingBuffer spikes_in_;
    RingBuffer currents_;

    //! Logger for all analog data
    UniversalDataLogger< iaf_psc_exp_htum > logger_;
  };

  // ----------------------------------------------------------------

  /**
   * Internal variables of the model.
   */
  struct Variables_
  {
    /** Amplitude of the synaptic current.
        This value is chosen such that a postsynaptic potential with
        weight one has an amplitude of 1 mV.
        @note mog - I assume this, not checked.
    */
    //    double PSCInitialValue_;

    // time evolution operator
    double P20_;
    double P11ex_;
    double P11in_;
    double P21ex_;
    double P21in_;
    double P22_;

    int RefractoryCountsAbs_;
    int RefractoryCountsTot_;
  };

  // Access functions for UniversalDataLogger -------------------------------

  //! Read out the real membrane potential
  double
  get_V_m_() const
  {
    return S_.V_m_;
  }
  double
  get_I_syn_ex_() const
  {
    return S_.i_syn_ex_;
  }
  double
  get_I_syn_in_() const
  {
    return S_.i_syn_in_;
  }

  // ----------------------------------------------------------------

  /**
   * Instances of private data structures for the different types
   * of data pertaining to the model.
   * @note The order of definitions is important for speed.
   * @{
   */
  Parameters_ P_;
  State_ S_;
  Variables_ V_;
  Buffers_ B_;
  /** @} */

  //! Mapping of recordables names to access functions
  static RecordablesMap< iaf_psc_exp_htum > recordablesMap_;
};


inline size_t
iaf_psc_exp_htum::send_test_event( Node& target, size_t receptor_type, synindex, bool )
{
  SpikeEvent e;
  e.set_sender( *this );
  return target.handles_test_event( e, receptor_type );
}

inline size_t
iaf_psc_exp_htum::handles_test_event( SpikeEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_psc_exp_htum::handles_test_event( CurrentEvent&, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return 0;
}

inline size_t
iaf_psc_exp_htum::handles_test_event( DataLoggingRequest& dlr, size_t receptor_type )
{
  if ( receptor_type != 0 )
  {
    throw UnknownReceptorType( receptor_type, get_name() );
  }
  return B_.logger_.connect_logging_device( dlr, recordablesMap_ );
}


inline void
iaf_psc_exp_htum::get_status( Dictionary& d ) const
{
  P_.get( d );
  S_.get( d, P_ );
  ArchivingNode::get_status( d );
  d[ names::recordables ] = recordablesMap_.get_list();
}

inline void
iaf_psc_exp_htum::set_status( const Dictionary& d )
{
  Parameters_ ptmp = P_;                        // temporary copy in case of errors
  const double delta_EL = ptmp.set( d, this );  // throws if BadProperty
  State_ stmp = S_;                             // temporary copy in case of errors
  stmp.set( d, ptmp, delta_EL, this );          // throws if BadProperty

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

#endif  // iaf_psc_exp_htum_H
