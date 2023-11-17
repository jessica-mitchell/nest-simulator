import nest
import matplotlib.pyplot as plt
import numpy as np

np.random.seed(123)
rng = np.random.default_rng()

# Parameters from paper
epop_params = {"g_AMPA_ext": 2.1,
               "g_AMPA": 0.05,
               "g_NMDA": 0.165,
               "g_GABA": 1.3,
               "tau_GABA": 5.0,
               "tau_AMPA": 2.0,
               "tau_decay_NMDA": 100.0,
               "alpha": 0.5,
               "conc_Mg2": 1.0,
               "g_L": 25.,               # leak conductance
               "E_L": -70.0,            # leak reversal potential
               "E_ex": 0.0,             # excitatory reversal potential
               "E_in": -70.0,           # inhibitory reversal potential
               "V_reset": -55.0,        # reset potential
               "V_th": -50.0,           # threshold
               "C_m": 500.0,            # membrane capacitance
               "t_ref": 2.0             # refreactory period
               }


ipop_params = {"g_AMPA_ext": 1.62,
               "g_AMPA": 0.04,
               "g_NMDA": 0.13,
               "g_GABA": 1.0,
               "tau_GABA": 5.0,
               "tau_AMPA": 2.0,
               "tau_decay_NMDA": 100.0,
               "alpha": 0.5,
               "conc_Mg2": 1.0,
               "g_L": 20.,               # leak conductance
               "E_L": -70.0,            # leak reversal potential
               "E_ex": 0.0,             # excitatory reversal potential
               "E_in": -70.0,           # inhibitory reversal potential
               "V_reset": -55.0,        # reset potential
               "V_th": -50.0,           # threshold
               "C_m": 200.0,            # membrane capacitance
               "t_ref": 1.0             # refreactory period
               }

simtime = 4000.
signal_start = 1000.
signal_duration = 2000.
signal_update_interval = 50.
f = 0.15 # proportion of neurons receiving signal inputs
w_plus = 1.7
w_minus = 1 - f * (w_plus - 1) / (1 - f)

NE = 1600
NI = 400

selective_pop1 = nest.Create("iaf_wang_2002", int(0.15 * NE), params=epop_params)
selective_pop2 = nest.Create("iaf_wang_2002", int(0.15 * NE), params=epop_params)
nonselective_pop = nest.Create("iaf_wang_2002", int(0.7 * NE), params=epop_params)
inhibitory_pop = nest.Create("iaf_wang_2002", NI, params=ipop_params)

mu_0 = 40.
rho_a = mu_0 / 100
rho_b = rho_a
c = 80.
sigma = 4.
mu_a = mu_0 + rho_a * c
mu_b = mu_0 - rho_b * c

num_updates = int(signal_duration / signal_update_interval)
update_times = np.arange(0, signal_duration, signal_update_interval)
update_times[0] = 0.1
rates_a = np.random.normal(mu_a, sigma, size=num_updates)
rates_b = np.random.normal(mu_b, sigma, size=num_updates)

poisson_a = nest.Create("inhomogeneous_poisson_generator",
                        params={"origin": signal_start-0.1,
                                "start": 0.,
                                "stop": signal_duration,
                                "rate_times": update_times,
                                "rate_values": rates_a})

poisson_b = nest.Create("inhomogeneous_poisson_generator",
                        params={"origin": signal_start-0.1,
                                "start": 0.,
                                "stop": signal_duration,
                                "rate_times": update_times,
                                "rate_values": rates_b})

poisson_0 = nest.Create("poisson_generator", params={"rate": 2400.})

syn_spec_pot = {"synapse_model": "static_synapse", "weight":w_plus, "delay":0.1, 'receptor_type': 0}
syn_spec_default = {"synapse_model": "static_synapse", "weight":1.0, "delay":0.1, 'receptor_type': 0}
syn_spec_dep = {"synapse_model": "static_synapse", "weight":w_minus, "delay":0.1, 'receptor_type': 0}
syn_spec_inhibitory = {"synapse_model": "static_synapse", "weight":-1.0, "delay":0.1, 'receptor_type': 0}
syn_spec_ext = {"synapse_model": "static_synapse", "weight":1., "delay":0.1, 'receptor_type': 1}

sr_nonselective = nest.Create("spike_recorder")
sr_selective1 = nest.Create("spike_recorder")
sr_selective2 = nest.Create("spike_recorder")
sr_inhibitory = nest.Create("spike_recorder")

mm_selective1 = nest.Create("multimeter", {"record_from": ["V_m", "s_NMDA", "s_AMPA", "s_AMPA_ext", "s_GABA"]})
mm_inhibitory = nest.Create("multimeter", {"record_from": ["V_m", "s_NMDA", "s_AMPA", "s_GABA"]})


nest.Connect(poisson_0,
             nonselective_pop + selective_pop1 + selective_pop2 + inhibitory_pop,
             conn_spec="all_to_all",
             syn_spec=syn_spec_ext)

nest.Connect(nonselective_pop,
             selective_pop1 + selective_pop2,
             conn_spec="all_to_all",
             syn_spec=syn_spec_dep)

nest.Connect(nonselective_pop,
             nonselective_pop + inhibitory_pop,
             conn_spec="all_to_all",
             syn_spec=syn_spec_default)

nest.Connect(selective_pop1,
             selective_pop2,
             conn_spec="all_to_all",
             syn_spec=syn_spec_dep)

nest.Connect(selective_pop2,
             selective_pop1,
             conn_spec="all_to_all",
             syn_spec=syn_spec_dep)

nest.Connect(selective_pop1 + selective_pop2,
             nonselective_pop + inhibitory_pop,
             conn_spec="all_to_all",
             syn_spec=syn_spec_default)

nest.Connect(inhibitory_pop,
             selective_pop1 + selective_pop2 + nonselective_pop + inhibitory_pop,
             conn_spec="all_to_all",
             syn_spec=syn_spec_inhibitory)

nest.Connect(poisson_a,
             selective_pop1,
             conn_spec="all_to_all",
             syn_spec=syn_spec_ext)

nest.Connect(poisson_b,
             selective_pop2,
             conn_spec="all_to_all",
             syn_spec=syn_spec_ext)

nest.Connect(nonselective_pop, sr_nonselective)
nest.Connect(selective_pop1, sr_selective1)
nest.Connect(selective_pop2, sr_selective2)
nest.Connect(inhibitory_pop, sr_inhibitory)


nest.Connect(mm_selective1, selective_pop1)
nest.Connect(mm_inhibitory, inhibitory_pop)

nest.Simulate(4000.)

spikes_nonselective = sr_nonselective.get("events", "times")
spikes_selective1 = sr_selective1.get("events", "times")
spikes_selective2 = sr_selective2.get("events", "times")
spikes_inhibitory = sr_inhibitory.get("events", "times")





senders = mm_selective1.get("events", "senders")
inds = senders == 1
vm = mm_selective1.get("events", "V_m")[inds]
s_AMPA = mm_selective1.get("events", "s_AMPA")[inds]
s_AMPA_ext = mm_selective1.get("events", "s_AMPA_ext")[inds]
s_GABA = mm_selective1.get("events", "s_GABA")[inds]
s_NMDA = mm_selective1.get("events", "s_NMDA")[inds]
