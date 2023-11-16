Breathe test
============

.. doxygenfile:: iaf_psc_alpha.h
   :sections: detaileddescription




Managers
--------


All managers implement the ``ManagerInterface`` (``initialize``, ``finalize``, ``getstatus``, ``cleanup``).


.. uml:: diagram.uml


.. doxygenclass:: nest::ManagerInterface


{% for item in cpp_list %}
{% if "Interface" not in item %}



.. .. doxygenclass::

{{ item }}


.. .. dropdown:: Members of {{item}}
   :color: light

   .. doxygenclass:: {{ item }}
      :members:
      :members-only:

{% endif %}
{% endfor %}

:cpp:class:`nest::ConnectionManager`
:cpp:class:`nest::KernelManager`
