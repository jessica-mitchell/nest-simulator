# -*- coding: utf-8 -*-
#
# aeif_cond_beta_multisynapse.py
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

"""
Example of an AEIF neuron with multiple synaptic rise and decay time constants
------------------------------------------------------------------------------



.. only:: html

  .. card:: Run this example as a Jupyter notebook
    :margin: auto
    :width: 50%
    :text-align: center

    .. image:: https://nest-simulator.org/TryItOnEBRAINS.png
         :target: https://lab.ebrains.eu/hub/user-redirect/git-pull?repo=https%3A%2F%2Fgithub.com%2Fnest%2Fnest-simulator-examples&urlpath=lab%2Ftree%2Fnest-simulator-examples%2Fnotebooks%2Fnotebooks%2Faeif_cond_beta_multisynapse.ipynb&branch=main

    For details and troubleshooting see :ref:`run_jupyter`.


"""

import nest
import numpy as np
import matplotlib.pyplot as plt

neuron = nest.Create('aeif_cond_beta_multisynapse')
nest.SetStatus(neuron, {"V_peak": 0.0, "a": 4.0, "b": 80.5})
nest.SetStatus(neuron, {'E_rev': [0.0, 0.0, 0.0, -85.0],
                        'tau_decay': [50.0, 20.0, 20.0, 20.0],
                        'tau_rise': [10.0, 10.0, 1.0, 1.0]})

spike = nest.Create('spike_generator', params={'spike_times':
                                               np.array([10.0])})

voltmeter = nest.Create('voltmeter')

delays = [1.0, 300.0, 500.0, 700.0]
w = [1.0, 1.0, 1.0, 1.0]
for syn in range(4):
    nest.Connect(spike, neuron, syn_spec={'synapse_model': 'static_synapse',
                                          'receptor_type': 1 + syn,
                                          'weight': w[syn],
                                          'delay': delays[syn]})

nest.Connect(voltmeter, neuron)

nest.Simulate(1000.0)

Vms = voltmeter.get("events", "V_m")
ts = voltmeter.get("events", "times")

plt.plot(ts, Vms)
plt.show()
