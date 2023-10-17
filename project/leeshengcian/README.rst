=================
Visualization-of-Dijkstra-Algorithm
=================

This Proposal shows the work flow and plans for the 2023 Autumn NYCU NSD term project


Basic Information
=================

GitHub Link : [https://github.com/leeshengcian/Visualization-of-Dijkstra-Algorithm/tree/main]

Dijkstra's algorithm is an algorithm for finding the shortest paths between 
nodes in a weighted graph, which may represent, for example, road networks. 
It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later.

Problem to Solve
================

For a given source node in the graph, the algorithm finds the shortest path between 
that node and every other. It can also be used for finding the shortest paths from 
a single node to a single destination node by stopping the algorithm 
once the shortest path to the destination node has been determined.

Note: The length of edge will be represented as multiples of "unit length"

possible usage:

1. Finding the shortest path of two intersections on a city map
2. Calculating Least-cost paths for instance to establish tracks of electricity lines or oil pipelines

.. image:: https://github.com/leeshengcian/Visualization-of-Dijkstra-Algorithm/blob/main/image/DijkstraDemo.gif


System Architecture
===================

.. image:: https://github.com/leeshengcian/Visualization-of-Dijkstra-Algorithm/blob/main/image/term_project_work_flow.png

API Description
===============

1. Dijkstra function in c++ will find the shortest path from the source node to each of the remaining nodes
    - dist[i] will store the shortest distance from source node to ith node
2. Use Pybind11 to wrap C++ functions for Python
3. Python file is responsible for drawing the graph
    - import networkx and matplotlib for plot work

Engineering Infrastructure
==========================

Describe how you plan to put together the engineering system:

1. Automatic build system: `CMake`
2. Version control: `git`
3. Testing framework: `pytest`
4. Documentation: `README.md`

Schedule
========

* Week 1 (10/30):
    - Study domain Knowledge for Dijkstra's Algorithm
    - Plot the original graph using networkx
* Week 2 (11/6):
    - Implement Dijkstra's on given graph
    - Prepare a presentation skeleton
* Week 3 (11/13):
    - Finish Dijkstra's Algorithm in c++ and write pybind11 wrapper
    - Further prepare for presentation
* Week 4 (11/20):
    - Finish Plot work in Python
* Week 5 (11/27):
    - Testing the correctness of algorithm and plot work
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

`Dijkstra's Algorithm <https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>`__

`NetworkX <https://networkx.org/>`__
