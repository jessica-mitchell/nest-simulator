Breathe test
============

Managers
--------


All managers implement the ``ManagerInterface`` (``initialize``, ``finalize``, ``getstatus``, ``cleanup``).

.. doxygenclass:: nest::ManagerInterface

{% for item in cpp_list %}
{% if "Manager" in item and "Interface" not in item %}


.. doxygenclass:: {{ item }}
   :no-link:

.. doxygenclass:: {{ item }}
   :members:
   :members-only:

{% endif %}
{% endfor %}


