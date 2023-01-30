# -*- coding: utf-8 -*-
#
# twoneurons.py
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
Two neuron example
------------------



.. only:: html

  .. card:: Run this example as a Jupyter notebook
    :margin: auto
    :width: 50%
    :text-align: center

    .. image:: https://nest-simulator.org/TryItOnEBRAINS.png
         :target: https://lab.ebrains.eu/hub/user-redirect/git-pull?repo=https%3A%2F%2Fgithub.com%2Fnest%2Fnest-simulator-examples&urlpath=lab%2Ftree%2Fnest-simulator-examples%2Fnotebooks%2Fnotebooks%2Ftwoneurons.ipynb&branch=main

    For details and troubleshooting see :ref:`run_jupyter`.


This script simulates two connected pre- and postsynaptic neurons.
The presynaptic neuron receives a constant external current,
and the membrane potential of both neurons are recorded.

See Also
~~~~~~~~

:doc:`one_neuron`

"""

###############################################################################
# First, we import all necessary modules for simulation, analysis and plotting.
# Additionally, we set the verbosity to suppress info messages and reset
# the kernel.

import nest
import nest.voltage_trace
import matplotlib.pyplot as plt

nest.set_verbosity("M_WARNING")
nest.ResetKernel()

###############################################################################
# Second, we create the two neurons and the recording device.

neuron_1 = nest.Create("iaf_psc_alpha")
neuron_2 = nest.Create("iaf_psc_alpha")
voltmeter = nest.Create("voltmeter")

###############################################################################
# Third, we set the external current of neuron 1.

neuron_1.I_e = 376.0

###############################################################################
# Fourth, we connect neuron 1 to neuron 2.
# Then, we connect a voltmeter to the two neurons.
# To learn more about the previous steps, please check out the
# :doc:`one neuron example <one_neuron>`.

weight = 20.0
delay = 1.0

nest.Connect(neuron_1, neuron_2, syn_spec={"weight": weight, "delay": delay})
nest.Connect(voltmeter, neuron_1)
nest.Connect(voltmeter, neuron_2)

###############################################################################
# Now we simulate the network using ``Simulate``, which takes the
# desired simulation time in milliseconds.

nest.Simulate(1000.0)

###############################################################################
# Finally, we plot the neurons' membrane potential as a function of
# time.

nest.voltage_trace.from_device(voltmeter)
plt.show()
