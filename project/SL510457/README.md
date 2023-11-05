# OptiRoute: Intelligent Travel Route Planner
This proposal outlines the workflow and plans for the NYCU NSD term project in Autumn 2023.

## Basic Information
OptiRoute focuses on solving the Traveling Salesman Problem (TSP), a fundamental challenge in optimization and computer science. At its core, TSP aims to find the most efficient route that visits a set of destinations and returns to the starting point.

In this project, we aim to develop a user-friendly system that allows users to input latitude and longitude coordinates for multiple destinations and, in turn, generates the optimal travel route, addressing various real-world applications, such as logistics, tour planning, and resource optimization.

GitHub Link : [ https://github.com/SL510457/TourTracer-Christofides-TSP-Visualizer ]

### Traveling Salesman Problem (TSP)
TSP is a NP hard problem. Given a set of cities and the distance between every pair of cities, the problem is to find the shortest possible route that visits each city exactly once and returns back to the original city. 

### Christofides algorithm
The Christofides algorithm is an approximation algorithm f or the Traveling Salesman Problem (TSP) that offers a good trade-off between solution quality and computational efficiency. It guarantees a solution within 1.5 times the optimal solution by using techniques like MST, minimum-weight perfect matching, Eulerian circuit.

### Haversine Formula
The Haversine Formula determines the great-circle distance between two points on a sphere given their longitudes and latitudes.

![](/image/HaversineFormula.png)



## Problem to Solve
Optimizing travel routes for multiple destinations is a common challenge in various fields. The problem involves finding the shortest route, which becomes increasingly complex as the number of destinations increases. Existing solutions are often lacking in user-friendliness.

This project aims to create a user-friendly system that allows users to input destination coordinates. We'll then use the `Haversine formula` and the `Christofides Algorithm` to find the most efficient travel route. This project bridges the gap between theory and practical application, providing an accessible solution for optimized travel planning.

![](/image/Chris.gif)

## Prospective Users
1. Tour Planning Enthusiasts
    - Targeting on travelers, tourists, and anyone planning personal trips and desire well-optimized travel experiences.
    - Features will include user-friendly input interfaces, customization options, and the ability to prioritize scenic routes and recommendations for accommodations and dining.
2. Logistics and Resource Optimization Users
    - Include those involved in transportation, energy management, agriculture, utility services, and similar sectors. They benefit from route optimization and resource allocation, reducing costs and enhancing efficiency.

## System Architecture
![](/image/flowchart.png)

## API Description
### Function in C++ file
1. `Haversine Funtion` determines the great-circle distance between two points on a sphere given their longitudes and latitudes.
2. `Node Transformation Function` use Haversine Formula to convert each destination's longitude , latitude and the distances between each pair of nodes, resulting in a weighted graph.
3. `Christofides Function` calculates the approximation solution to TSP through a given set of nodes.

### Function in python file
1. `Visualize` for visualizing the TSP graph, including the nodes and the approximate solution obtained through the Christofides algorithm.

 `Pybind11 Wrapper for C++ Functions` enabling seamless access from Python.

## Engineering Infrastructure

1. Automatic build system: `CMake`
2. Version control: `git`
3. Testing framework: `pytest`
4. Documentation: `README.md`


## Schedule
Planning phase (8 weeks from 10/30 to mm/dd):
| Week | Date | 內容 |
|---|---|---|
| 1 | 10/30 | - Study  for TSP, Christofides algorithm and Haversine Formula <br> - Start coding the function of `Haversine Function` <br> - Prepare a presentation skeleton|
| 2 | 11/6 | - Finish the function for the `Node Transformation Function`<br> - Start coding the function of `Christofides Function` <br> - Further prepare for presentation|
| 3 | 11/13 | - Finish `Christofides Function` in C++ and write a pybind11 wrapper <br> - Further prepare for presentation|
| 4 | 11/20 | - Finish Plot work in Python|
| 5 | 11/27 | - Testing the correctness of the algorithm and plot work|
| 6 | 12/4 | - Implement CMake file <br> - Make slides and prepare for presentation|
| 7 | 12/11 | - Testing if the system build works <br> - Write the Documentation <br> - Make slides and prepare for presentation|
| 8 | 12/18.. | - Finish writing Documentation <br> - Make slides and prepare for presentation|



## References
Traveling Salesman Problem:

https://en.wikipedia.org/wiki/Travelling_salesman_problem

Christofides algorithm:

https://stemlounge.com/animated-algorithms-for-the-traveling-salesman-problem/

Haversine Formula:

https://www.youtube.com/watch?v=HaGj0DjX8W8

to be added...
