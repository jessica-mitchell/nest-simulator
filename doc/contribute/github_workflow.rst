GitHub workflow
====================

The `NEST <http://www.nest-simulator.org/>`__ development team uses
`Git <https://git-scm.com/>`__ for version control. If you would like to
**contribute code or documentation**, the following
sections document the general steps required to set up a working
installation of Git.

This document is heavily based on the `NumPy Developer Documentation <https://github.com/numpy/numpy/tree/master/doc/source/dev/gitwash>`_


Basic setup of git
---------------------

.. note::

 If you have Git set up already, skip to the section :ref:`fork`.
 If you're ready to start making your changes to the code or documentation, skip to :ref:`the
 section describing the development workflow <workflow>`.

For more information on using Git, please refer to the `Git
book <http://git-scm.com/book/en/v2>`__.

Installation and global setup
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-  `Install
   Git <http://git-scm.com/book/en/v2/Getting-Started-Installing-Git>`__
-  Introduce yourself to Git:

.. code-block:: sh

   git config --global user.email you@yourdomain.example.com
   git config --global user.name "Your name goes here"

Setting up your GitHub account
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The `NEST <http://www.nest-simulator.org/>`__ source code is hosted in a
public repository on `GitHub <https://en.wikipedia.org/wiki/GitHub>`__.
If you don’t have a GitHub account already, please `create
one <http://github.com/>`__.

You then need to configure your account to allow write access - please
see the `article on generating SSH
keys <http://help.github.com/articles/generating-ssh-keys/>`__ on the
`GitHub help website <https://help.github.com/>`__.

--------------

.. _fork:

Making your own copy (fork) of NEST
-------------------------------------

This needs to be done only once. The instructions here are very similar
to the `instructions at GitHub <http://help.github.com/forking/>`__ -
which you can refer to for more details. This documentation includes a
version specific to `NEST <http://www.nest-simulator.org/>`__.

Create your own forked copy of NEST
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-  `Login <https://github.com/login>`__ to your GitHub account.
-  Go to the `NEST source code repository on
   GitHub <https://github.com/nest/nest-simulator>`__.
-  Click on the *Fork* button:

.. figure:: ../_static/img/fork-button.png
   :alt: fork button

After a short pause, you should find yourself at the home page for your
own forked copy of `NEST <http://www.nest-simulator.org/>`__.

Downloading your fork
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

After forking the repository, you need to download it to your local
computer to work with the code.

Command list
`````````````

The following commands should do it. The next section explains the
commands.

.. code-block:: sh

   git clone git@github.com:your-user-name/nest-simulator.git
   cd nest-simulator
   git remote add upstream git://github.com/nest/nest-simulator.git

Commands explained
`````````````````````
**Clone your fork**

.. code-block:: sh

   git clone git@github.com:your-user-name/nest-simulator.git

This downloads your fork to your local system. Investigate. Change
directory to your new repository: ``cd nest-simulator``. Then
``git branch -a`` to show you all branches. You’ll get something like:

.. code-block:: sh

   * master
   remotes/origin/master

This tells you that you are currently on the ``master`` branch, and that
you also have a ``remote`` connection to ``origin/master``. The
``master`` branch is the default branch and this is where code that has
been reviewed and tested resides. ``origin/master`` is just a copy of
the ``master`` branch on your system on the ``remote``.

What remote repository is ``remote/origin``? Try ``git remote -v`` to
see the web address for the remote. It should point to your GitHub fork.

Next, you connect your local copy to the central `NEST GitHub
repository <https://github.com/nest/nest-simulator>`__, so that you can
keep your local copy and remote fork up to date in the future.
Conventionally, the main source code repository is called ``upstream``.

**Link your repository to the upstream repository**

.. code-block:: sh

   cd nest-simulator
   git remote add upstream git://github.com/nest/nest-simulator.git

Note that we’ve used ``git://`` in the web address instead of ``git@``.
The ``git://`` web address is read only and ensures that you don’t make
any accidental changes to the ``upstream`` repository (if you have
permissions to write to it, of course).

Check that you have a new ``remote`` set up with ``git remote -v show``.
You should see something like this:

.. code-block:: sh

   upstream     git://github.com/nest/nest-simulator.git (fetch)
   upstream     git://github.com/nest/nest-simulator.git (push)
   origin       git@github.com:your-user-name/nest-simulator.git (fetch)
   origin       git@github.com:your-user-name/nest-simulator.git (push)

--------------

.. _workflow:

Suggested development workflow
----------------------------------

Once you’ve already set up your :ref:`forked copy <fork>` of the `NEST source code
repository <https://github.com/nest/nest-simulator>`__, you can now
start making changes to it. The following sections document the
suggested Git workflow.

Basic overview of workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In short:

1. Start a *new branch* for each set of changes that you intend to make.
   See the section on :ref:`making a new feature
   branch <feature_branch>` below.
2. Hack away! See the section that documents the :ref:`editing
   workflow <edit_workflow>`.
3. When you are satisfied with your edits, push these changes to your
   own GitHub fork, and open a pull request to notify the development
   team that you’d like to make these changes available at the
   ``upstream`` repository. Please follow our guidelines for :ref:`creating a pull request <pull_request>`.

This suggested workflow helps to keep the source code repository
properly organized. It also ensures that the history of changes that
have been made to the source code (called ``commit history``) remains
tidy - making it easier to follow.

.. _feature_branch:

Make a new feature branch
`````````````````````````````

Before you make any changes, ensure that your local copy is up to date
with the ``upstream`` repository.

.. code-block:: sh

   # go to (checkout) the default master branch
   git checkout master
   # download (fetch) changes from upstream
   git fetch upstream
   # update your master branch - merge any changes that have been made upstream
   git merge upstream/master --ff-only
   # update the remote for your fork
   git push origin master

We suggest using the ``--ff-only`` flag since it ensures that a new
commit is not created when you merge the changes from ``upstream`` into
your ``master`` branch. Using this minimises the occurrence of
superfluous merge commits in the commit history.

Now that you have the latest version of the source code, create a new
branch for your work and check it out:

.. code-block:: sh

   git checkout -b my-new-feature master

This starts a new branch called ``my-new-feature`` from ``master``.

It is extremely important to work on the latest available source code.
If you work on old code, it is possible that in the meantime, someone
else has already made more changes to the same files that you have also
edited. This will result in `merge
conflicts <https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging#Basic-Merge-Conflicts>`__
and resolving these is extra work for both the development team and you.
It also muddles up the ``commit history`` of the source code.

.. _edit_workflow:

Editing workflow - command list
``````````````````````````````````
.. code-block:: sh

   # improve 'modified_file' with your text editor/IDE
   # confirm what files have changed in the repository
   git status
   # review the changes you've made
   git diff # Optional
   # inform git that you want to save these changes
   git add modified_file
   # save these changes
   git commit
   # push these changes to the remote for your fork
   git push origin my-new-feature

Editing workflow - commands explained
``````````````````````````````````````````

-  Make some changes. When you feel that you’ve made a complete, working
   set of related changes, move on to the next steps.
-  Please ensure that you have followed the coding guidelines for
   :doc:`C++ <../developer_space/coding_guidelines_c++>` and :doc:`SLI <../developer_space/coding_guidelines_sli>`.
-  Then test your changes by building the source code and running the
   tests. (Usually ``cmake ...; make; make install; make installcheck``.
   Please see the
   `INSTALL <https://github.com/nest/nest-simulator/blob/master/INSTALL>`__
   file for details.)
-  Check which files have changed with ``git status``. You’ll see a
   listing like this one

.. code-block:: sh

    On branch my-new-feature
    Changed but not updated:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

      modified:   README

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

      INSTALL
    no changes added to commit (use "git add" and/or "git commit -a")

-  Compare the changes with the previous version using ``git diff``.
   This brings up a simple text browser interface that highlights the
   difference between your files and the previous version like this:


.. code-block:: none

   diff --git a/development_workflow.md b/development_workflow.md
   index f05f0cd..e581f00 100644
   --- a/development_workflow.md
   +++ b/development_workflow.md
   @@ -8,17 +8,22 @@ layout: index
    [NEST Issue Tracker]: <https://github.com/nest/nest-simulator/issues> "NEST Issue Tracker"
    [NEST private]: <https://github.com/nest/nest-private>

   -# Getting started with Git development

   -This section and the next describe in detail how to set up git for working with
   -the NEST source code. If you have git already set up, skip to
   -[Development workflow](#development-workflow)
   -This document is heavily based on the
   -[NumPy Developer Documentation](https://github.com/numpy/numpy/tree/master/doc/source/dev/gitwash) :)
   +# Basic Git Setup

   -## Basic Git setup
   +The [NEST] development team uses [Git](https://git-scm.com/) for version control.
   +The following sections document the general steps required to set up . If you
   +have Git set up already, skip to
   +[the section describing the development workflow](#development-workflow).
   +This document is heavily based on the [NumPy Developer
   +Documentation](https://github.com/numpy/numpy/tree/master/doc/source/dev/gitwash)
   +:)

-  Inform Git of what modified or new files you want to save (stage)
   using ``git add modified_file``. This puts the files into a
   ``staging area``, which is a list of files that will be added to your
   next commit. Only add files that have related, complete changes.
   Leave files with unfinished changes for later commits.

-  To commit the staged files into the local copy of your repo, do
   ``git commit``. Write a clear Git commit message that describes the
   changes that you have made. (Please read `this article on writing
   commit messages <http://chris.beams.io/posts/git-commit/>`__). If a
   commit fixes an open issue on the `GitHub issue
   tracker <https://github.com/nest/nest-simulator/issues>`__, include
   ``Fixes #issue_number`` in the commit message. GitHub finds such
   keywords and closes the issue automatically when the pull request is
   merged. For a list of all keywords you can use, refer to `this GitHub
   help
   page <https://help.github.com/articles/closing-issues-via-commit-messages/>`__.
   After saving your message and closing the editor, your commit will be
   saved.

-  Push the changes to your forked repo on
   `GitHub <http://github.com/>`__

.. code-block:: sh

   git push origin my-new-feature

Assuming you have followed the instructions in these pages, git will
create a default link to your `GitHub <http://github.com/>`__ repo
called ``origin``. In git >= 1.7 you can ensure that the link to origin
is permanently set by using the ``--set-upstream`` option:

.. code-block:: sh

   git push --set-upstream origin my-new-feature

From now on git will know that ``my-new-feature`` is related to the
``my-new-feature`` branch in your own `GitHub <http://github.com/>`__
repo. Subsequent push calls are then simplified to the following

.. code-block:: sh

   git push

It often happens that while you were working on your edits, new commits
have been added to ``upstream`` that affect your work. In this case, you
will need to reposition your commits on the new master. Please follow
the instructions on `rebasing your commits on
master <#rebasing-on-master>`__ section of this document to see how this
is handled.

Next, we see how to create a pull request.

Create a pull request
~~~~~~~~~~~~~~~~~~~~~~

When you feel your work is finished, ensure you have looked over :ref:`our criteria for reviewing
pull requests <pull_request>`.
GitHub has a nice help page that outlines the process for `submitting
pull
requests <https://help.github.com/articles/using-pull-requests/#initiating-the-pull-request>`__.
Your pull request will usually be reviewed by other
`NEST <http://www.nest-simulator.org/>`__ developers using the :doc:`code
review guidelines <../developer_space/code_review_guidelines>`.

-------------

For more advanced cases, please see our :doc:`developer space <../developer_space/advanced_git_workflow>`.

