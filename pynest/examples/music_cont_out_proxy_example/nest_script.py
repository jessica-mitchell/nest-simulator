#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# nest_script.py
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
Music example
--------------


.. only:: html

  .. card:: Run this example as a Jupyter notebook
    :margin: auto
    :width: 50%
    :text-align: center

    .. image:: https://nest-simulator.org/TryItOnEBRAINS.png
         :target: https://lab.ebrains.eu/hub/user-redirect/git-pull?repo=https%3A%2F%2Fgithub.com%2Fnest%2Fnest-simulator-examples&urlpath=lab%2Ftree%2Fnest-simulator-examples%2Fnotebooks%2Fnotebooks%2Fmusic_cont_out_proxy_example%2Fnest_script.ipynb&branch=main

    For details and troubleshooting see :ref:`run_jupyter`.



This example runs 2 NEST instances and one receiver instance. Neurons on
the NEST instances are observed by the music_cont_out_proxy and their
values are forwarded through MUSIC to the receiver.

"""
import nest

proxy = nest.Create('music_cont_out_proxy', 1)
proxy.port_name = 'out'
proxy.set(record_from=["V_m"], interval=0.1)

neuron_grp = nest.Create('iaf_cond_exp', 2)
proxy.targets = neuron_grp
neuron_grp[0].I_e = 300.
neuron_grp[1].I_e = 600.

nest.Simulate(200)
