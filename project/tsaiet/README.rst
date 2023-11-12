=================
Optimizing Traffic Flow with Ford-Fulkerson
=================

.. .. This is a template to specify what your project is and the execution plan.  You
.. will find it is difficult to plan for things that you are not sure about.  Do
.. your best.

.. .. You are encouraged to use this plain-text `reStructuredText
..   <https://docutils.sourceforge.io/rst.html>`__ format.  :download:`Download
..   this file. <project_template.rst>`

.. .. Please do give your project a name that clearly states the subject and is short
.. enough for people to remember.

.. .. Additional documents or files may be used.  They should be added in the
.. repository.

Basic Information
=================

.. .. Create a GitHub repository to host your project and add the URL here.  The
.. GitHub repository has an 'About' field, in which you are encouraged to write a
.. simple statement (preferably one sentence) to introduce the project.

Ford-Fulkerson is a mathematical tool used to optimize the flow of resources or 
entities through a network, which can be applied to improve traffic flow in a 
city or region. In this project, we aim to use Ford-Fulkerson to enhance traffic 
safety and reduce traffic congestion.

We can represent city roads as a directed graph, each intersection is modeled as a 
node, and roads are represented as edges with maximum capacities determined by 
factors such as "the length of the road", "and the speed limitof the road", 
"the number of lanes". The source node is designated as "home," and the 
sink node is identified as "office."

* Github Repository: [https://github.com/tsaiet/Optimizing-Traffic-Flow-with-Ford-Fulkerson]

Problem to Solve
================

.. .. Describe the problem or the set of problems you want to solve.  Include
.. necessary background information without making it lengthy.

.. .. Some points may help you organize the problem description:

.. .. 1. The field or industry of the problem.
.. 2. The physics and/or the mathematics behind the problem.
.. 3. The algorithm or numerical method that should be applied for solving the
..    problem.

Traffic congestion is a significant challenge in transportation and urban planning, 
leading to many issues, including longer commute times, increased traffic accident rate.
By optimizing traffic flow using maximum flow algorithms, the project seeks to mitigate 
congestion and its associated problems. Ford-Fulkerson aims to optimize the flow of 
vehicles through road networks. 

Prospective Users
=================

.. .. Describe the users of your software and how they will use it.  It is OK to
.. combine this section with the previous one (`Problem to solve`_).

This project targets traffic application developers, taxi drivers, citizens, 
and government.

System Architecture
===================

.. .. Analyze how your system takes input, produces results, provide interface, and
.. performs any other operations.  Describe the system's work flow.  You may
.. consider to use a flow chart but it is not required.  Specify the constraints
.. assumed in your system.  Describe the modularization of the system.

.. image:: https://github.com/tsaiet/nsdhw_23au/blob/tsaiet-project-proposal/project/tsaiet/System%20Architecture.png

API Description
===============

.. .. Show how your system can be programmed.  You are supposed to implement the
.. system using both C++ and Python.  Describe how a user writes a script in the
.. system.

Users have the option to include the library by linking it into their own project.

C++ users: 

``#include "Ford-Fulkerson-library.hpp"``

Python users: 

``import Ford-Fulkerson-library``

Engineering Infrastructure
==========================

.. .. Describe how you plan to put together the engineering system:

.. .. 1. Automatic build system and how to build your program
.. 2. Version control (show how you will use it)
.. 3. Testing framework
.. 4. Documentation

.. .. Some of the above information should be included in the documentation in your
.. software.

.. .. You may use continuous integration, but it is not required.  If you use it,
.. describe how it works in your code development.

1. Automatic build system: `CMake`
2. Version control: `git`
3. Testing framework: `Pytest`
4. Documentation: `README.rst`
5. Continuous Integration: `Github Actions`

Schedule
========

.. .. Itemize the work to do and list them in a timeline.  Estimate the efforts of
.. each item before the project starts.

.. .. The schedule is expected to be adjusted during the development.  A schedule to
.. accurately predict everything in the development is impossible and unnecessary.
.. But the initial estimate is important, for the baseline becomes concrete when
.. we adjust the plan.

.. .. To start, you can list the to-do items on a weekly basis and assume the
.. development of the project takes 8 weeks:

* Planning phase (7 weeks from 11/06 to 12/18):
Week 1 (11/06):
----------
- survey some references about Ford-Fulkerson
- search the way to present the result
- make the Python interface for input

Week 2 (11/13):
----------
- Finish the Ford-Fulkerson algorithm in C++

Week 3 (11/20):
----------
- Finish the Pytest and Pybind

Week 4 (11/27):
----------
- Finish the presentation in Python

Week 5 (12/04):
----------
- Write the Continuous Integration

Week 6 (12/11):
----------
- Buffer week

Week 7 (12/18):
----------
- Prepare for presentation

References
==========

.. List the external references for the information provided in the proposal.

- https://github.com/tobyatgithub/pythonMaximumFlowTraffic
- https://en.wikipedia.org/wiki/Ford-Fulkerson_algorithm
