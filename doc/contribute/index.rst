Contribute to NEST
=======================

Thanks for taking the time to contribute!

The NEST simulator is a scientific tool and as such it is never ready and constantly changing to meet the needs of novel neuroscientific endeavors.
Here you'll find all you need to know about contributiong to NEST.

* :ref:`Code of Conduct <code_conduct>`
* :ref:`I have a question about NEST <mailing_list>`
* :ref:`How can I contribute? <contribute>`
    * :ref:`Reporting bugs and other issues <submit_issue>`
    * :ref:`Suggesting enhancements  or new models <enhancement>`
    * :ref:`Contributing code or documentation <git_workflow>`
    * :ref:`How can I share a module I created using NEST? <user-contributed_modules>`
    * :ref:`Become a member <member>`

* :ref:`Styleguides and conventions <styleguides>`

----

.. _code_conduct:

Code of Conduct
-------------------
-- use an adaptation of the contributor covenant code of conduct?

 * :doc:`code_of_conduct`

----

 .. _mailing_list:

I have a question about NEST!
--------------------------------

.. note::

 Please don't file an issue on Github to ask a question.

Check out our FAQ [nc]

We have an official :doc:`NEST user mailing list <guidelines_mailinglist>`, which is intended to be a forum:

* to discuss questions on the usage of NEST
* to exchange ideas and solutions regarding specific problems
* to share interesting and exciting news about NEST

All NEST core developers are subscribed to this list and participate in the discussions and
try to answer questions promptly. We strongly encourage participation from our
entire community: Our philosophy is that **all users profit by sharing their experience**.

Subscribe to the mailing list :doc:`here <guidelines_mailinglist>`


----


.. _contribute:

How can I contribute?
-----------------------

.. _submit_issue:

Submit an issue on Github
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Did you notice a bug or potential area for improvement in NEST?

.. pull-quote::

  Before submitting an issue, please use the appropriate template:

   * For bug reports:  :ref:`good_bug_report`

   * For enhancements and new models: :ref:`enhancement`


..   .. image:: ../img/sample_issue.png
      :width: 600 px
      :align: center



.. _git_workflow:

Make changes to the code or documentation using the GitHub workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

NEST uses git for code and documentation development and versioning.
Before making changes, please review the following sections to ensure your request will be considered for merging into the  NEST source code.


**If you are new to git or GitHub or just need a refresher**, please see the section :doc:`using the GitHub workflow <github_workflow>`
to see how to create a fork of our Git repository and use the basic commands of git in your workflow.

Make  your changes
```````````````````

* Create a branch in your fork of NEST (avoid working direclty on the *master* branch)
* Ensure your changes to code or documentation follow the relevant :ref:`styleguides <styleguides>`
* Ensure your :doc:`git commits <git_commit_messages>` are split into logical units
* Make sure NEST compiles and has no new warnings

.. _pull_requests:

Prepare your pull request
`````````````````````````
For us to make a proper review of your pull request, we ask that you ensure
your contribution meets the following criteria:

#. If your pull request resolves an *issue*, `write 'Resolves #issue-number' in the title of the pull request <https://github.com/blog/957-introducing-issue-mentions>`_
#. Follow all instructions in the template :doc:`what to include in my pull request <template_pullrequest>`
#. After you submit your pull request, verify that all checks have passed in the Travis CI https://travis-ci.org/nest/nest-simulator
#. Sign the `Contributor license agreement <https://github.com/nest/nest-simulator/blob/master/extras/NEST_Contributor_Agreement.pdf>`_

 .. .. image:: ../_static/img/travis_pass.png
    :width: 600 px
    :align: center


Code review
````````````

In general, the rule is that each pull request needs to be approved by the CI platform and at least two reviewers.
For changes labeled "not code" or "minor" (e.g. changes in documentation, fixes for typos, etc.), the release manager can waive the need for code review and just accept the OK from Travis in order to merge the request.
Reviewers are requested to comply to our :doc:`code review guidelines <../developer_space/code_review_guidelines>`.
Once the reviewers are satisfied with the pull request, a maintainer will merge it into the master branch.

New features like SLI or PyNEST functions, neuron or synapse models need to be accompanied by one or more tests written either in SLI or Python. New features for the NEST kernel need a test written in SLI.
Each change to the code has to be reflected also in the corresponding examples and documentation.

**We will not review a pull request unless the naming conventions and coding guidelines have been followed!**


.. note::

    Maintainers have full discretion to close issues and pull requests if

    * too much information is missing,
    * the appropriate template/styleguide was not followed,
    * contributor is not responding to comments,
    * the request is deemed unsuitable for NEST or is addressed elsewhere

    Maintainers will provide a reason for closing the issue/rejecting a pull request in the comments section

.. _user-contributed_modules:

User-contributed modules
~~~~~~~~~~~~~~~~~~~~~~~~~

The NEST simulator can be extended by `external modules <https://github.com/nest/nest-simulator/wiki/NEST-Modules>`_
that are loaded at runtime. Some users share their work and you can use the
additional functionality of these custom user contributed NEST-modules in your
simulation. For comments and questions regarding the independently developed
modules please contact the corresponding developers directly.

If you wrote an extension yourself and want us to link to your Github repository, just
click the ``manage topics`` button under the title of your main repository page
and add the topic nest-module.

.. image:: ../img/manage_topics.png
    :width: 600 px
    :align: center

.. _member:

Become a NEST member
~~~~~~~~~~~~~~~~~~~~

If you would like to be actively involved in the NEST Initiative and support its
goals, please see our `member page <http://www.nest-initiative.org/membership>`_.


----

.. _styleguides:

Styleguides
--------------

We have created several styleguides to maintain consistency and improve
readability and efficiency of our code and documentation. Please refer to the relevant
styleguide for any change you want to make to code or documentation.


* :doc:`How to make good git_commit_messages`

* :doc:`Cite NEST in your publication or poster! <citing_nest>`

* :doc:`Guidelines for contributing to documentation <guidelines_docs/doc_guide>` (including PyNEST example scripts)

* **NEW** `Create models with our python-based modeling language  NESTML <https://github.com/nest/nestml>`_

* :doc:`Guidelines for creating new models using C++ <guidelines_create_model/index>`

**Developer**

* :doc:`Guidelines for reviewing code <../developer_space/code_review_guidelines>`

* :doc:`Guidelines for C++ <../developer_space/coding_guidelines_c++>`

* :doc:`Guidelines for SLI <../developer_space/coding_guidelines_sli>`
