# -*- coding: utf-8 -*-
#
# gaussex.py
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
Gaussian probabilistic kernel
-----------------------------



.. only:: html

  .. card:: Run this example as a Jupyter notebook
    :margin: auto
    :width: 50%
    :text-align: center

    .. image:: https://nest-simulator.org/TryItOnEBRAINS.png
         :target: https://lab.ebrains.eu/hub/user-redirect/git-pull?repo=https%3A%2F%2Fgithub.com%2Fnest%2Fnest-simulator-examples&urlpath=lab%2Ftree%2Fnest-simulator-examples%2Fnotebooks%2Fnotebooks%2Fspatial%2Fgaussex.ipynb&branch=main

    For details and troubleshooting see :ref:`run_jupyter`.


Create two populations on a 30x30 grid and connect them using a Gaussian probabilistic kernel
BCCN Tutorial @ CNS*09
Hans Ekkehard Plesser, UMB
"""

import matplotlib.pyplot as plt
import numpy as np
import nest

nest.ResetKernel()

#####################################################################
# create two test layers
pos = nest.spatial.grid(shape=[30, 30], extent=[3., 3.])

#####################################################################
# create and connect two populations
a = nest.Create('iaf_psc_alpha', positions=pos)
b = nest.Create('iaf_psc_alpha', positions=pos)

cdict = {'rule': 'pairwise_bernoulli',
         'p': nest.spatial_distributions.gaussian(nest.spatial.distance,
                                                  std=0.5),
         'mask': {'circular': {'radius': 3.0}}}

nest.Connect(a, b, cdict)

#####################################################################
# plot targets of neurons in different grid locations
#
# plot targets of two source neurons into same figure, with mask
# use different colors

for src_index, color, cmap in [(30 * 15 + 15, 'blue', 'Blues'), (0, 'green', 'Greens')]:
    # obtain node id for center
    src = a[src_index:src_index + 1]
    fig = plt.figure()
    nest.PlotTargets(src, b, mask=cdict['mask'], probability_parameter=cdict['p'],
                     src_color=color, tgt_color=color, mask_color=color,
                     probability_cmap=cmap, src_size=100,
                     fig=fig)

    # beautify
    plt.axes().set_xticks(np.arange(-1.5, 1.55, 0.5))
    plt.axes().set_yticks(np.arange(-1.5, 1.55, 0.5))
    plt.grid(True)
    plt.axis([-2.0, 2.0, -2.0, 2.0])
    plt.axes().set_aspect('equal', 'box')
    plt.title('Connection targets, Gaussian kernel')

plt.show()

# plt.savefig('gaussex.pdf')
