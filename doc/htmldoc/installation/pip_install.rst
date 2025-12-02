NEST pip Installation and First Steps Guide
===========================================

.. contents:: Table of Contents
   :depth: 3
   :local:

Introduction
============

NEST is a Python package providing bindings for the NEST neural network simulator. This guide
covers installation from PyPI and getting started with basic usage.

Prerequisites
=============

System Requirements
-------------------

- **Operating System**: Linux (Ubuntu/Debian recommended), macOS, or Windows WSL2
- **Python**: 3.9 to 3.13 (as specified in ``pyproject.toml``)
- **Architecture**: x86_64 (amd64) - see ``cibuildwheel`` configuration

System Requirements
-------------------

**For PyPI Installation**:

- **Python**: 3.9 to 3.13
- **pip**: Latest version (``pip install --upgrade pip``)
- **Virtual environment** (recommended): ``python3 -m venv nest-env``

**No additional system dependencies required** - the PyPI package includes all necessary
compiled libraries.

Installation
============

Install from PyPI
-----------------

.. code-block:: bash

   # Create and activate virtual environment
   python3 -m venv nest-env
   source nest-env/bin/activate  # On Windows: nest-env\Scripts\activate

   # Install NEST
   pip install --upgrade pip
   pip install nest-simulator

   # Verify installation
   python -c "import nest; print('NEST version:', nest.__version__)"

.. note::
   The package name is ``nest-simulator`` but you import it as ``nest`` in Python.

**Install with Optional Dependencies**

.. code-block:: bash

   # Install with NESTML support (neural modeling language)
   pip install nest-simulator[nestml]

   # Install with NEST Desktop (web-based GUI)
   pip install nest-simulator[desktop]

   # Install the NEST Server (REST API) dependencies
   pip install nest-simulator[server]

   # Install multiple optional dependencies
   pip install nest-simulator[nestml,desktop]
   pip install nest-simulator[nestml,server]
   pip install nest-simulator[nestml,desktop,server]

Available optional dependencies:

- **nestml**: Enables NESTML (NEST Modeling Language) for creating custom neuron and synapse
  models using a domain-specific language. Ideal for researchers developing new model types.
- **desktop**: Adds NEST Desktop web-based graphical user interface for visual network
  construction, parameter exploration, and simulation control through a browser interface.
- **server**: Provides dependencies for the NEST Server REST API for remote simulation control,
  enabling web applications, distributed computing, and integration with other tools via HTTP
  requests.

Verification and First Steps
============================

Basic Import and System Info Test
----------------------------------

Based on ``hl_api_info.py``:

.. code-block:: bash

   python -c "
   import nest
   print('NEST version:', nest.__version__)
   print('NEST kernel info:')
   nest.sysinfo()
   nest.authors()
   "

Example Scripts
---------------

NEST includes built-in examples you can run directly:

.. code-block:: bash

   # Run built-in examples
   python -c "import nest; nest.helpdesk()"  # Opens documentation with examples

Simple Neural Network Example
------------------------------

.. code-block:: python

   import nest
   import numpy as np
   import matplotlib.pyplot as plt

   # Reset NEST kernel
   nest.ResetKernel()

   # Create neurons
   neuron = nest.Create("iaf_psc_alpha", 2)

   # Create and connect spike generator
   spike_generator = nest.Create("spike_generator", params={"spike_times": [20.0, 80.0]})
   nest.Connect(spike_generator, neuron[0])

   # Create voltmeter to record membrane potential
   voltmeter = nest.Create("voltmeter")
   nest.Connect(voltmeter, neuron)

   # Simulate
   nest.Simulate(100.0)

   # Get and plot results
   events = voltmeter.events
   plt.figure(figsize=(10, 6))
   plt.plot(events["times"], events["V_m"])
   plt.xlabel("Time [ms]")
   plt.ylabel("Membrane potential [mV]")
   plt.title("Neuron membrane potential")
   plt.show()

Test Installation
------------------

.. code-block:: bash

   # Test that NEST is working correctly
   python -c "import nest; nest.sysinfo(); print('Installation successful!')"

Package Features
================

**Included Features**:

The PyPI package comes with these features built-in:

- **Core NEST simulator** with Python bindings
- **GSL** (GNU Scientific Library) for mathematical functions
- **Boost** libraries for enhanced C++ functionality
- **OpenMP** support for parallel computing
- **HDF5** support for data input/output
- **Standard neuron and synapse models**

**Optional Python Dependencies**:

.. code-block:: bash

   # For neural modeling language support
   pip install nest-simulator[nestml]

   # For web-based graphical interface
   pip install nest-simulator[desktop]

   # For REST API server functionality
   pip install nest-simulator[server]

   # For data analysis and visualization (recommended)
   pip install matplotlib jupyter pandas seaborn

Troubleshooting
===============

Common Issues
-------------

**1. Import Error: "No module named 'nest'"**

.. code-block:: bash

   # Ensure you're in the correct virtual environment
   which python
   pip list | grep nest-simulator

   # Verify the package is installed correctly
   python -c "import nest; print('NEST installed successfully')"

**2. Installation Issues**

.. code-block:: bash

   # Upgrade pip if installation fails
   pip install --upgrade pip

   # Try installing in a fresh virtual environment
   python3 -m venv fresh-env
   source fresh-env/bin/activate
   pip install nest-simulator

**3. Python Version Compatibility**

.. code-block:: bash

   # Check Python version (must be 3.9-3.13)
   python --version

   # If version is too old, install a newer Python version

Getting Help
------------

- **Documentation**: Visit `NEST Simulator Documentation <https://nest-simulator.readthedocs.io/>`_
- **Issues**: Report bugs at `GitHub Issues <https://github.com/nest/nest-simulator/issues>`_
- **Community**: Join the `NEST Users Mailing List <mailto:users@nest-simulator.org>`_
- **System Info**: Run ``python -c "import nest; nest.sysinfo()"`` for debugging
- **Help Desk**: Use ``nest.helpdesk()`` to open documentation in browser

Next Steps
==========

- Read the `NEST documentation <https://nest-simulator.readthedocs.io/>`_ for detailed API
  reference
- Check out `PyNEST tutorials
  <https://nest-simulator.readthedocs.io/en/stable/tutorials/index.html>`_ for learning materials
- Try the built-in examples: ``python -c "import nest; nest.helpdesk()"``
- Install optional dependencies:

  - ``pip install nest-simulator[nestml]`` for neural modeling language support
  - ``pip install nest-simulator[desktop]`` for web-based GUI
  - ``pip install nest-simulator[server]`` for REST API functionality
- Explore advanced features like custom neuron models and network simulations

**What's Included**:

- **Core NEST simulator**: All standard neuron and synapse models
- **GSL**: GNU Scientific Library for mathematical functions (compiled in)
- **Boost**: C++ libraries for enhanced functionality (compiled in)
- **OpenMP**: Parallel computing support on single machines (compiled in)
- **HDF5**: Data input/output capabilities (compiled in)
- **Python dependencies**: NumPy, SciPy, Matplotlib, Pandas, H5Py, MPI4Py, Cython

**Optional Extensions**:

- **NESTML**: Neural modeling language for custom models
- **NEST Desktop**: Web-based graphical user interface
- **NEST Server**: REST API for web applications and remote control

The PyPI package provides a complete, ready-to-use NEST installation with no additional system
dependencies required.
