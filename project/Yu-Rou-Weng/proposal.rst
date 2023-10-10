=================
Mesh Data Converter: A Simple C++ libaray for Converting NASA's Plot3D to SU2
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

The conversion of NASA's Plot3D to SU2 file format pertains to mesh data conversion.

In the realm of mesh data conversion, numerical solutions for partial differential
equations (PDEs) rely on the discretization of space. The entities that describe this
discretized space are known as grids or meshes.  Here are 3 types of codes standing out 
to conducting effective numerical analysis: (i) a mesh generator creates the grid, (ii) 
a solver computes the solution, and (iii) a visualizer provides the analysis. Among these 
components, mesh data holds serve as a central element connecting these codes.

Converting NASA's Plot3D to SU2 file format is a key aspect of this mesh data conversion 
process, allowing seamless integration and utilization of the numerical solutions within 
different computational frameworks.

Problem to Solve
================

.. Describe the problem or the set of problems you want to solve.  Include
.. necessary background information without making it lengthy.

.. Some points may help you organize the problem description:

.. 1. The field or industry of the problem.
.. 2. The physics and/or the mathematics behind the problem.
.. 3. The algorithm or numerical method that should be applied for solving the
   problem.

Plot3D and SU2 server as good examples of the numerical analytical codes:

1.Plot3D is a file format which can only store structured grid and result data and 
  remains a only file format in the filed of Computaional Fluid Dynamic(CFD).

2.SU2 is a suite of open-source software tools written in C++ for the numerical solution 
  of partial differential equations (PDE) and performing PDE-constrained optimization.

When dealing with numerical analysis, the mesh data format differs between Plot3D and SU2. 
Plot3D uses structured mesh as input, while SU2 uses unstructured mesh for solving fluid dynamics.

The goal of this project is to create a file format converter that can translate Plot3D mesh data 
into a format compatible with SU2. This converter will function as a standalone executable, facilitating 
data exchange between different programs(codes). Also, the converter will be integrated to [modmesh](https://github.com/solvcon/modmesh)
Schedule to 
serve as a useful plugged-in library for easier automation.

Prospective Users
=================

.. Describe the users of your software and how they will use it.  It is OK to
.. combine this section with the previous one (`Problem to solve`_).

1.Modmesh: (Will add more explanation after discussions)

2.Fluid dynamics professionals or researchers who need to exchange mesh data between Plot3D and SU2 when 
using different simulation software.

3.In the aerospace and automotive industries, engineers frequently rely on computational fluid dynamics (CFD) 
simulations. This converter offers a more precise mesh data conversion solution for their simulations.

4.Computer Scientists, Students, and educators who are working in computational fluid dynamics studies and experiments.

System Architecture
===================
(Will finish after discussion with yy teacher)

.. Analyze how your system takes input, produces results, provide interface, and
.. erforms any other operations.  Describe the system's work flow.  You may
.. consider to use a flow chart but it is not required.  Specify the constraints
.. assumed in your system.  Describe the modularization of the system.

API Description
===============
(Still in progress, will finish after discussion with yy teacher)

1.Fuctions in c++ will include ReadPlot3DData、WriteSU2Data、ConvertPlot3DToSU2

2.Use pybind11 for wrapping

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

1. Automatic build system:**CMake**
2. Version control: Git
3. Testing framework: **Pytest** 
4. Documentation: README(or Notion)、 [PyDoc](https://marketplace.visualstudio.com/items?itemName=njpwerner.autodocstring)

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

* Planning phase (8 weeks from mm/dd to mm/dd):
* Week 1 (10/30):
         1.Study domain knwoledges
         2.Prepare a presentaion skeleton
* Week 2 (11/6):
         1.Search and gather suitable Plot3D mesh data format and comprehend structures and characteristic of both Plot3D and SU2.
         2.Start to design the conversion in C++ if 1. is done in advance
* Week 3 (11/13):Implement conversion in C++
* Week 4 (11/20):Implement conversion in C++ and bind to python
* Week 5 (11/27):
         1.Implement a CMake file for a draft 
         2.Add some works and adjust the presentation draft
* Week 6 (12/4):
         1.Write unit tests and refactor codes.
         2.Check whether if my presentation draft follow the grading criteria.
         3.Integrate to modmesh (depends on remaining time)
* Week 7 (12/11):Buffer time for debugging and and documentation
* Week 8 (12/18):Refine and finish the final project, prepare for the presentation

References
==========

.. List the external references for the information provided in the proposal.

- [Plot3D Documentation](https://nasa.github.io/Plot3D_utilities/_build/html/)
- [Plot3d File Format for Grid and Solution Files](https://www.grc.nasa.gov/www/wind/valid/plot3d.html)
- [SU2](https://su2code.github.io/)
- To be added…
