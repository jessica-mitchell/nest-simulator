Managers in NEST
================



All managers implement the ``ManagerInterface`` (``initialize``, ``finalize``, ``getstatus``, ``cleanup``).


Manager Interface
-----------------


.. doxygenclass:: nest::ManagerInterface
   :no-link:

.. doxygenclass:: nest::ManagerInterface
    :members:
    :members-only:


Kernel Manager
--------------

.. doxygenclass:: nest::KernelManager



{% for item in cpp_list %}
{% if "Manager" in item and "Interface" not in item and "Kernel" not in item  %}


{{ item }}
-------------------------------

.. doxygenclass:: {{ item }}

.. .. dropdown:: Members of {{item}}
   :color: light

   .. doxygenclass:: {{ item }}
      :members:
      :members-only:

{% endif %}
{% endfor %}


{% for item in cpp_list %}
{% if "Manager" not in item %}

{{ item }}
{% endif %}
{% endfor %}
