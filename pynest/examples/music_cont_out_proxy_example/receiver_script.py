#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# receiver_script.py
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
Music example receiver script
------------------------------


.. only:: html

  .. card:: Run this example as a Jupyter notebook
    :margin: auto
    :width: 50%
    :text-align: center

    .. image:: https://nest-simulator.org/TryItOnEBRAINS.png
         :target: https://lab.ebrains.eu/hub/user-redirect/git-pull?repo=https%3A%2F%2Fgithub.com%2Fnest%2Fnest-simulator-examples&urlpath=lab%2Ftree%2Fnest-simulator-examples%2Fnotebooks%2Fnotebooks%2Fmusic_cont_out_proxy_example%2Freceiver_script.ipynb&branch=main

    For details and troubleshooting see :ref:`run_jupyter`.


"""

import sys
import music
import numpy
from itertools import takewhile, dropwhile

setup = music.Setup()
stoptime = setup.config("stoptime")
timestep = setup.config("timestep")

comm = setup.comm
rank = comm.Get_rank()

pin = setup.publishContInput("in")
data = numpy.array([0.0, 0.0], dtype=numpy.double)
pin.map(data, interpolate=False)

runtime = setup.runtime(timestep)
mintime = timestep
maxtime = stoptime+timestep
start = dropwhile(lambda t: t < mintime, runtime)
times = takewhile(lambda t: t < maxtime, start)
for time in times:
    val = data
    sys.stdout.write(f"t={time}\treceiver {rank}: received {val}\n")
