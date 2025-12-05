NEST pip Installation Guide
===========================

.. contents::
   :local:

Introduction
============

NEST is a neural network simulator with Python bindings. This guide covers installation of the ``pynest-ng`` package from PyPI.

Prerequisites
=============

- **Python**: 3.9 to 3.13
- **Operating System**: Linux, macOS
- **Architecture**: x86_64 (64-bit)

Installation
============

Basic Installation
------------------

.. code-block:: bash

   # Create virtual environment (recommended)
   python3 -m venv nest-env
   source nest-env/bin/activate

   # Install NEST
   pip install --upgrade pip
   pip install pynest-ng

   # Verify installation
   python -c "import nest; print('NEST version:', nest.__version__)"

.. note::
   The package name is ``pynest-ng`` but you import it as ``nest`` in Python.

Optional Features
-----------------

Available options:

- **sonata**: HDF5-based network file format support
- **server**: REST API server dependencies
- **examples**: Additional packages for running examples
- **full**: All optional features

.. code-block:: bash

   # Install with Sonata format support (HDF5-based network files)
   pip install pynest-ng[sonata]

   # Install with server capabilities (REST API)
   pip install pynest-ng[server]

   # Install with example dependencies
   pip install pynest-ng[examples]

   # Install everything
   pip install pynest-ng[full]

   # Combine multiple options
   pip install pynest-ng[sonata,server]
   pip install pynest-ng[examples,server]

Verification
============

Simple Example
--------------

.. code-block:: python

   import nest
   import matplotlib.pyplot as plt

   # Reset and create network
   nest.ResetKernel()

   # Create neurons and devices
   neuron = nest.Create("iaf_psc_alpha", 2)
   spike_gen = nest.Create("spike_generator", params={"spike_times": [20.0, 80.0]})
   voltmeter = nest.Create("voltmeter")

   # Connect network
   nest.Connect(spike_gen, neuron[0])
   nest.Connect(voltmeter, neuron)

   # Simulate
   nest.Simulate(100.0)

   # Plot results
   events = voltmeter.events
   plt.plot(events["times"], events["V_m"])
   plt.xlabel("Time [ms]")
   plt.ylabel("Membrane potential [mV]")
   plt.show()

Package Contents
================

**Core Features (always included):**

- NEST simulator with Python bindings
- Standard neuron and synapse models
- GSL (GNU Scientific Library)
- Boost libraries
- OpenMP parallelization
- Basic dependencies: numpy, matplotlib, cython

**Optional Features:**

- **Sonata support**: HDF5-based network format (macOS, Alpine Linux, Debian/Ubuntu)
- **Server mode**: REST API for remote control
- **Examples**: Additional visualization and analysis tools

Troubleshooting
===============

Common Issues
-------------

**Import Error**

.. code-block:: bash

   # Verify installation
   pip list | grep pynest-ng
   python -c "import nest; print('OK')"

**Python Version Issues**

.. code-block:: bash

   # Check Python version
   python --version  # Must be 3.9-3.13

**Installation Failures**

.. code-block:: bash

   # Clean install
   pip install --upgrade pip
   python3 -m venv clean-env
   source clean-env/bin/activate
   pip install pynest-ng

Getting Help
============

- **Documentation**: https://nest-simulator.readthedocs.io/
- **Issues**: https://github.com/nest/nest-simulator/issues
- **Mailing List**: users@nest-simulator.org
- **System Info**: ``python -c "import nest; nest.sysinfo()"``

Next Steps
==========

1. Read the `NEST tutorials <https://nest-simulator.readthedocs.io/en/stable/tutorials/>`_
2. Explore the `model gallery <https://nest-simulator.readthedocs.io/en/stable/models/>`_
