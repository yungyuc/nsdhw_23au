=================
Polygon-Clipping
=================

This Proposal shows the work flow and plans for the 2023 Autumn NYCU NSD term project


Basic Information
=================

GitHub Link : `repo <https://github.com/leeshengcian/Polygon-Clipping>`_

Polygon clipping are important operations in algorithm design, especially for computer graphics, computer vision, and computational geometry.

Polygon clipping is the process of cutting off parts of a polygon that lie outside a given boundary.
For example, if you have a triangle that extends beyond the edges of a window, polygon clipping is the operation that trims the triangle to fit inside the window.

.. image:: https://github.com/leeshengcian/Polygon-Clipping/blob/main/image/poly-clip.png

Problem to Solve
================

For Polygon Clipping problem, there are many algorithms are capable of solving this problem, 
such as **Sutherland–Hodgman algorithm**, **Greiner–Hormann clipping algorithm**, 
**Vatti clipping algorithm**, **Weiler–Atherton clipping algorithm**.

**Sutherland–Hodgman algorithm**, which is one of the most widely used algorithms for polygon clipping. 
However, it has some drawbacks, such as being **inefficient and slow** for large or complex polygons. 
This is because it must process every edge of the polygon against every edge of the boundary. 
Additionally, it can lead to **numerical errors** and **rounding issues** 
from the use of floating-point arithmetic and intersection calculations.

In this work, we focus on improving the Sutherland–Hodgman algorithm, make it more suitable for large or complex polygons, 
and also decrease the numerical errors.

System Architecture
===================

to be planned...

API Description
===============

to be planned...

Engineering Infrastructure
==========================

1. Automatic build system: `CMake`
2. Version control: `git`
3. Testing framework: `pytest`
4. Documentation: `README.md`

Schedule
========

* Week 1 (10/30):
    - Study domain Knowledge for Polygon Clipping Algorithm
    - Implement **Sutherland–Hodgman algorithm**
* Week 2 (11/6):
    - Study **Weiler-Atherton algorithm** and **Greiner-Hormann algorithm**
    - Redesign Sutherland–Hodgman algorithm based on its drawbacks
* Week 3 (11/13):
    - Study **Vatti clipping algorithm**
    - Compare redesigned Sutherland–Hodgman algorithm with other three
* Week 4 (11/20):
    - Finish Sutherland–Hodgman Algorithm in c++ and write pybind11 wrapper
    - to be planned...
* Week 5 (11/27):
    - Testing the correctness of algorithm and show comparison among four algorithms
    - to be planned...
* Week 6 (12/4):
    - Implement CMake file
    - Make slides and prepare for presentation
* Week 7 (12/11):
    - Testing if the system build work
    - Write the Documentation
    - Make slides and prepare for presentation
* Week 8 (12/18):
    - Finish writing Documentation
    - Make slides and prepare for presentation

References
==========

`Sutherland–Hodgman algorithm <https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm>`_

`Sutherland–Hodgman algorithm Implementation <https://www.geeksforgeeks.org/polygon-clipping-sutherland-hodgman-algorithm/>`_

`Greiner–Hormann clipping algorithm <https://en.wikipedia.org/wiki/Greiner%E2%80%93Hormann_clipping_algorithm>`_

`Vatti clipping algorithm <https://en.wikipedia.org/wiki/Vatti_clipping_algorithm>`_

`Weiler–Atherton clipping algorithm <https://en.wikipedia.org/wiki/Weiler%E2%80%93Atherton_clipping_algorithm>`_
