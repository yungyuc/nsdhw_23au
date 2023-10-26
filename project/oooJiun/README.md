# PolyMap: Polygon-Based 2D Map Generator

## Basic Information

- GitHub Repository: https://github.com/oooJiun/PolyMap

PolyMap is a tool that empowers users to create custom 2D maps with a user-friendly Python interface. 
To achieve this goal, PolyMap will use boolean operations, such as AND, OR, NOT, and XOR, on polygons to generate the map.


## Problem to Solve

In Euclidean space, our objective is to perform polygonal Boolean operations for extracting geometric properties from graphics. 
These operations are valuable for tasks like combining polygons, terrain elevation modeling, and random map generation.

The goal of this project is to let user can define the polygons by themselves and calculate the boolean operations in a efficient way to generate a 2D map.
Users can design custom maps for games, visualize geographic data, and develop training simulations.


## System Architecture

- Input: Users define polygons, terrain parameters, and map parameters through the graphical user interface.
- Processing: The system applies Boolean operations, elevation modeling, and randomization to generate maps.
- Output: The generated 2D maps are displayed in the graphical user interface and can be exported in common image formats.
- Constraints: Assumes that users have basic knowledge of map design concepts.
- Modularization: The system is divided into modules for polygon creation, Boolean operations, elevation modeling, and map rendering.


## API Description

The system can be scripted using both C++ and Python.
Example Script (Python):
```python
from map_generator import MapGenerator

# Create a MapGenerator instance
generator = MapGenerator()

# Define polygons, terrain parameters, and map parameters
polygons = [...]
terrain_params = {...}
map_params = {...}

# Generate the map
generated_map = generator.generate_map(polygons, terrain_params, map_params)

# Display or export the map
generated_map.display()
generated_map.export('output_map.png')
```


## Engineering Infrastructure

1. Automatic build system: `Makefile`
2. Version control: `git`
3. Testing framework: `pytest`
4. Documentation: `README.md`


## Schedule

* Week 1 (10/30): Learn the algorithm for boolean operations on polygons
* Week 2 (11/06): Design data structures and algorithms
* Week 3 (11/13): Implement the boolean operations on polygons algorithm in C++
* Week 4 (11/20): Refine the algorithm
* Week 5 (11/27): Develop UI in python
* Week 6 (12/04): Design testing and CI
* Week 7 (12/11): Checking and refine the UI
* Week 8 (12/18): Finalize the project and prepare the presentation


## References

Boolean operations on polygons in JavaScript: https://github.com/velipso/polybooljs

