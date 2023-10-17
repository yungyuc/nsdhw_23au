# TourTracer : Christofides-TSP-Solver
This proposal outlines the workflow and plans for the NYCU NSD term project in Autumn 2023.

## Basic Information
### Traveling Salesman Problem (TSP)
TSP is a NP hard problem. Given a set of cities and the distance between every pair of cities, the problem is to find the shortest possible route that visits each city exactly once and returns back to the original city. 

### Christofides algorithm
The Christofides algorithm is an approximation algorithm for the Traveling Salesman Problem (TSP) that offers a good trade-off between solution quality and computational efficiency. It guarantees a solution within 1.5 times the optimal solution by using techniques like MST, minimum-weight perfect matching, Eulerian circuit.


GitHub Link : [ https://github.com/SL510457/TourTracer-Christofides-TSP-Visualizer ]



## Problem to Solve
Given a graph with nodes and weighted edges, find a Hamiltonian cycle in the graph that minimizes the total distance traveled. 

Various applications in transportation, logistics, and optimization require efficient TSP solutions. However, due to diverse data formats and proprietary restrictions, current systems lack compatibility.

This project seeks to create an interoperable TSP solution, standardizing data formats for seamless integration. It enhances efficiency, reduces complexity, and promotes TSP problem-solving across domains.


(Still need to make more changes and additions)


## Prospective Users
1. Transportation and Aviation Professionals
<!-- This user group encompasses transportation planners, airports, and airlines. These professionals focus on optimizing transportation routes, whether it's public transportation within cities or flight operations in the aviation industry. They can benefit from our project by efficiently planning bus routes, optimizing flight paths, reducing travel times, and improving transportation services. -->
2. Mapping and Navigation Services
<!-- Companies like Google Maps and other navigation service providers can integrate our solution to enhance their route optimization algorithms, ensuring users are provided with the most efficient directions and travel routes. -->
3. Tourism and Event Management
<!-- Event planners and tourism agencies can utilize the tool to optimize tour itineraries, plan event routes, and offer efficient travel options to tourists, enhancing their overall experience. -->
4. Robotics and Autonomous Vehicles:
<!-- Researchers and developers in the field of robotics and autonomous vehicles can integrate this solution to improve path planning for robots and self-driving cars, making them more efficient and safe. -->
(Still need to make more changes and additions)


## System Architecture
...

## API Description
1. `Christofides Function` in C++ is designed to find an approximation solution to TSP. It calculates the shortest route through a given set of nodes.
2. `Pybind11 Wrapper for C++ Functions` enabling seamless access from Python. 
3. `Python Graph Visualization` for visualizing the TSP graph, including the nodes and the approximate solution obtained through the Christofides algorithm.

## Engineering Infrastructure

1. Automatic build system: `CMake`
2. Version control: `git`
3. Testing framework: `pytest`
4. Documentation: `README.md`

## Schedule
Planning phase (6 weeks from mm/dd to mm/dd):
* Week 1 (10/30):
    - Study domain Knowledge for TSP and Christofides algorithm
    - Prepare a presentation skeleton

* Week 2 (11/6):
    - Implement Christofides algorithm on given graph
    -  Further prepare for presentation
* Week 3 (11/13):
    - Finish Christofides algorithm in c++ and write pybind11 wrapper
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

## References
...
