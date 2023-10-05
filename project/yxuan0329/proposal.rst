=================
R-Tree Spatio-Temporal Search Engine
=================

.. This is a template to specify what your project is and the execution plan.  You
.. will find it is difficult to plan for things that you are not sure about.  Do
.. your best.

.. note::

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

R-tree is a tree structure designed for efficient spatial access, it has been widely used in geographic 
searching. However, when searching for data in map system, it is crucial to consider temporal features to enhance searching performance.
The R-Tree Spatio-Temporal Search Engine aims to provide a search engine for users to query multi-dimensional data with both 
spatial and temporal information. In this project, we will provide a demonstration of the R-tree search engine, enabling users to enter 
queries and receive a set of results that include the nearest distance and the best time-matched entities.


Problem to Solve
================

.. Describe the problem or the set of problems you want to solve.  Include
.. necessary background information without making it lengthy.

.. Some points may help you organize the problem description:

.. 1. The field or industry of the problem.
.. 2. The physics and/or the mathematics behind the problem.
.. 3. The algorithm or numerical method that should be applied for solving the
..    problem.

R-tree is a data structure renowned for its exceptional performance in searching multi-dimensional data, 
it plays a pivotal role in various applications, particularly in spatial information systems 
such as maps. However, beyond spatial information, data in map system should also take temporal 
feature in considerations for better searching performance. When searching nearest location on map system,
users should be able to see different sorting results depending on their specified searching time. 
In other words, the users should be able to receive different searching results for the same query at different days and times.

The goal of this project is to integrate temporal data into the indexing process, 
effectively creating a new temporal dimension within the R-tree structure. We aspire to enable users to not only search 
by spatial attributes but also to incorporate temporal considerations into their queries. Furthermore, this project seeks 
to refine the organization of data within the R-tree, prioritizing results based on temporal relevance, thereby delivering 
a more comprehensive and responsive mapping experience.



Prospective Users
=================

.. Describe the users of your software and how they will use it.  It is OK to
.. combine this section with the previous one (`Problem to solve`_).

This project aims to provide to users that want to search multidimensional data including spatial and temporal features.

System Architecture
===================

.. Analyze how your system takes input, produces results, provide interface, and
.. performs any other operations.  Describe the system's work flow.  You may
.. consider to use a flow chart but it is not required.  Specify the constraints
.. assumed in your system.  Describe the modularization of the system.

Implementation Plan
===================

1. Frontend design:
The search engine will provide a simple UI with one text block for users to enter query for searching, 
and one text block list for showing the searching results.

2. Datasets:
Generate the database with about 50 map data entry by myself for validating the R-tree algorithm can works correctly. 


API Description
===============

.. Show how your system can be programmed.  You are supposed to implement the
.. system using both C++ and Python.  Describe how a user writes a script in the
.. system.

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
* Week 1 (10/30): Survey some reference about R-tree implementation
* Week 2 (11/06): Create database with about 50-100 data
* Week 3 (11/13): Implement R-tree with C++
* Week 4 (11/20): Implement R-tree with C++
* Week 5 (11/27): Implement front-end of the search engine
* Week 6 (12/04): Improve the R-tree structure with temporal feature
* Week 7 (12/11): Testing, finish up the project and the documentation
* Week 8 (12/18): Make slides and prepare for the presentation

References
==========
.. List the external references for the information provided in the proposal.
- [R-tree definition on wikipedia](https://en.wikipedia.org/wiki/R-tree)
- [R-tree Based Indexing of General Spatio-Temporal Data](https://timecenter.cs.aau.dk/wp-content/uploads/2022/12/TR-45.pdf)
- [R-Trees: A Dynamic Index Structure for Spatial Searching](https://link.springer.com/referenceworkentry/10.1007/978-3-319-23519-6_1151-2)

