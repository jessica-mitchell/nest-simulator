.. _good_bug_report:

How do I submit a *good* bug report?
--------------------------------------

To make it easier for the developers to understand and solve the
problem, please include the following information in your bug report, if
applicable.

Before creating a bug report, please check the `current list <https://github.com/nest/nest-simulator/issues>`_
of issues on GitHub as you might find out that you don’t need to create one.

.. pull-quote::

  **Descriptive title**

  [Write a title that clearly and concisely states the issue]

  **Description**

  [Description of the issue]

  **Steps to reproduce**

  1. [First Step]
  2. [Second Step]
  3. [and so on...]

  **Expected behavior:** [What you expect to happen]

  **Actual behavior:** [What actually happens]

  **Reproduces how often:**

  [What percentage of the time does it reproduce? Always/Sometimes/Unsure]

.. warning::

  **Version**

  * [Specify the release version or Git commit of NEST]

  * [Specify which platform and operating system version you use]

.. admonition:: something

  **Additional information**

  [Any additional information, configuration or data that might be necessary to reproduce the issue such as

.. note::

  * The file ``config.log`` from the build directory and the output of the configure script.

  * The contents of the ``reports`` directory in the build directory.]

----

**Submit your issue here:** https://github.com/nest/nest-simulator/issues

.. note::

 If you are unsure if the problem you have is indeed a bug, you can always write to the
 :doc:`mailing list <../contribute/guidelines_mailinglist>` first and ask the community.

Submit other issues
------------------------

You can also create an issue regarding errors in the code or documentation that are not bugs.
In these cases, please ensure you follow the :ref:`prerequisites <submit_issue>` above and
include as much information as you can regarding the location of the error (e.g. /path/to/file and line number or webpage name and section name)
and if possible, a solution to the error.

