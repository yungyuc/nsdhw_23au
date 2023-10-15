=================
R-Tree Spatial Search Engine
=================


..   You are encouraged to use this plain-text `reStructuredText
..   <https://docutils.sourceforge.io/rst.html>`__ format.  :download:`Download
..   this file. <project_template.rst>`

.. Please do give your project a name that clearly states the subject and is short
.. enough for people to remember.

.. Additional documents or files may be used.  They should be added in the
.. repository.

Basic Information
=================

.. Create a GitHub repository to host your project and add the URL here.  The
.. GitHub repository has an 'About' field, in which you are encouraged to write a
.. simple statement (preferably one sentence) to introduce the project.

R-tree is a tree structure designed for efficient spatial data access. It has 
been widely used in real-world geographic searching because of its exceptional 
searching performance. In this project, we aim to serve a R-tree library to 
provide an efficient search for end-users. 


Problem to Solve
================

.. Describe the problem or the set of problems you want to solve.  Include
.. necessary background information without making it lengthy.

.. Some points may help you organize the problem description:

.. 1. The field or industry of the problem.
.. 2. The physics and/or the mathematics behind the problem.
.. 3. The algorithm or numerical method that should be applied for solving the
..    problem.

In geographic searching application, the users would expect to swiftly receive 
a set of searching results upon entering the query. In real-world application, 
rapid access to geospatial information is crucial for the users, as delays can 
result in inconveniences and increased costs.  

The fundamental concept behind the R-tree is to encapsulate nearby objects 
related to the searching target within a minimum bounding rectangle. Our goal 
is to develop an efficient R-tree library for spatial data retrieval that can 
address large-scale spatial data searches. 


Prospective Users
=================

.. Describe the users of your software and how they will use it.  It is OK to
.. combine this section with the previous one (`Problem to solve`_).

This project aims to provide to users who seek to build an efficient 
multi-dimensional searching service.


System Architecture
===================

.. Analyze how your system takes input, produces results, provide interface, and
.. performs any other operations.  Describe the system's work flow.  You may
.. consider to use a flow chart but it is not required.  Specify the constraints
.. assumed in your system.  Describe the modularization of the system.
Architecture
---------

The library would include:

- ``build_tree``: build a r-tree
- ``search``: search for the available results in r-tree
- ``insert``: insert a node in r-tree
- ``delete``: delete a node in r-tree

Datasets
---------

Randomly generate about 50-100 map data entry by Python for validating the 
R-tree algorithm can works correctly. 


API Description
===============

.. Show how your system can be programmed.  You are supposed to implement the
.. system using both C++ and Python.  Describe how a user writes a script in the
.. system.

The users can include the library by linking in their project. 
The C++ users can simply link by adding include file.

``#include "r-tree-library.hpp"``

The Python users can import the library by adding the script.

``import r-tree-library``


Engineering Infrastructure
==========================

.. Describe how you plan to put together the engineering system:

.. 1. Automatic build system and how to build your program
.. 2. Version control (show how you will use it)
.. 3. Testing framework
.. 4. Documentation

.. Some of the above information should be included in the documentation in your
.. software.

.. You may use continuous integration, but it is not required.  If you use it,
.. describe how it works in your code development.

1. Automatic build system: CMake
2. Version control: git
3. Testing framework: Pytest
4. Documentation: README.rst

  Testing data source: random-generated testing datasets including location and the 
  name of the place. 

  The testing mesurement includes correctness and time performance.

Schedule
========

.. Itemize the work to do and list them in a timeline.  Estimate the efforts of
.. each item before the project starts.

.. The schedule is expected to be adjusted during the development.  A schedule to
.. accurately predict everything in the development is impossible and unnecessary.
.. But the initial estimate is important, for the baseline becomes concrete when
.. we adjust the plan.

.. To start, you can list the to-do items on a weekly basis and assume the
.. development of the project takes 8 weeks:

* Planning phase (6 weeks from mm/dd to mm/dd):
Week 1 (10/30)
---------
- Survey some reference about the data structure and implementation
- Survey some existing R-tree libraries and run
- Create a few testing dataset for testing the existing libraries

Week 2 (11/06)
---------
- Create about 50-100 testing datasets for future use
- Design the C++ classes architecture

Week 3 (11/13)
---------
- Implement R-tree with C++: ``build_tree``, ``search``

Week 4 (11/20)
---------
- Implement R-tree with C++: ``insert``, ``delete``

Week 5 (11/27)
---------
- Implement R-tree with C++
- Refactor the code if needed 

Week 6 (12/04)
---------
- Testing the features with pytest

Week 7 (12/11)
---------
- Finish up the project and the documentation
- Prepare for the slides
Week 8 (12/18)
---------
- Prepare for the presentation

References
==========
.. List the external references for the information provided in the proposal.
- https://en.wikipedia.org/wiki/R-tree
- https://timecenter.cs.aau.dk/wp-content/uploads/2022/12/TR-45.pdf
- https://link.springer.com/referenceworkentry/10.1007/978-3-319-23519-6_1151-2
