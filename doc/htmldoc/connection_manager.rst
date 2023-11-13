Connection manager
==================

On user level we always use `Synapse`. In code this is always a `connection`
since it is not necessarily the biological entity,
but may be an abstract learning rule or device connection.

.. uml::

  !include <C4/C4_Component>
  'AddComponentType("manager")
  HIDE_STEREOTYPE()
  Person(user, "User")

  Boundary(manager, "ConnectionManager") {
      Component(connman, "ConnectionManager")
      ComponentDb(conndb, "Connections")
      Component(connbuilder, "ConnBuilder")
      Component(connmod, "ConnectorModel")
  }
  Component(nodeman, "NodeManager")
  Component(model, "ModelManager")
  Rel(user, connman, "nest.connect()")
  Rel(connman, connbuilder, "creates\n& owns")
  Rel(connbuilder, connman, "calls connect_()")
  Rel(connman, connmod, "as instrcuted from connbuilder")
  BiRel(connbuilder, model, "check model")
  BiRel(connman, nodeman, "obtain source & target nodes")
  Rel(connmod, conndb, "create data")

.. .. doxygenclass:: nest::ConnectionManager


.. .. doxygenclass:: nest::ConnectionManager
   :no-link:
   :members:
   :members-only:
