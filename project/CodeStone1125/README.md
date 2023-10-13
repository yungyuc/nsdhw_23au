# 2D Collision Detector


## Basic Information

Simulate how different type of shape collide in a 2D map.

* github repository: [https://github.com/CodeStone1125/2DCollisionDetector](https://github.com/CodeStone1125/2DCollisionDetector)

## Problem to Solve

The objective of this system is to calculate scenarios for the most common shapes in
a 2D map, such as rectangles, circles, and polygons. Before we dive deeper into the 
topic, let's first discuss the "Axis-Aligned Bounding Box" (AABB) algorithm. It forms
the basisfor many collision detection systems in 2D graphics and game development due
to its simplicity and efficiency. Moreover, in the 2D world, AABB can effectively handle 
approximate collision detection.

However, in many cases, we not only need to deal with hundreds but thousands of collisions
simultaneously. Iterating through every object can be time-consuming, so we introduce the 
concept of a 'Quadtree.' This data structure enables efficient space separation and management
by dividing the space into quadrants. It facilitates quick collision checks by concentrating 
on potential collision areas, significantly improving performance and reducing unnecessary
calculations. Additionally, the Quadtree can adapt to various scenarios, ensuring high efficiency.

In summary, the Quadtree plays a vital role in enhancing performance, resulting in a 
smoother gaming experience. It also provides developers with the flexibility and control
needed to handle different types of collisions and interactions effectively.

![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/75069f10-594b-40b4-8407-5b047b39980c)


Therefore, in this project, my focus will be on efficiently managing a large number of 
collision detections using Quadtree optimization.

## Prospective users

* Game Developer: Determine whether something in a game world is attach by a character is very
  common in game developing. There are even games making this as one of their main features, like
  [Super Mario](https://zh.wikipedia.org/zh-tw/%E8%B6%85%E7%BA%A7%E9%A9%AC%E5%8A%9B%E6%AC%A7%E7%B3%BB%E5%88%97)
  and [Pokemon](https://zh.wikipedia.org/wiki/%E5%AE%9D%E5%8F%AF%E6%A2%A6%E7%B3%BB%E5%88%97#%E9%81%8A%E6%88%B2)

| ![Super Mario](./pictures/Mario.png) | ![Pokemon](./pictures/pokemon.png) |
|:-----------------------------------:|:-----------------------------------:|
| **Super Mario** |**Pokemon**|

* Collision Prevention for Automation Equipment: Robots and automation devices used in industrial
   automation need to ensure that they do not collide or interfere with each other while
   performing tasks.2D collision detection can monitor the positions of individual machine
   components to prevent unnecessary collisions, enhance production efficiency, and safeguard equipment.

## System Architecture



| ![](./pictures/system_architechture.png) |
|:-----------------------------------:|
| **System flow chart** |

## API Description

* Python API:
  * `addItem(start, end, varItem)`: create a Item on the map and return its id
  * `rmItem(item_id)`: remove the wall by its id
  * `moveItem(dest)`: move item to the destination coordinate
  * `collideObj(items)`: call the c++ api and show the events result by the items collision

* C++ API:
  * `collideObj(items)`: calculate all the items that collide on 2D map and return item id
     and events result by the items collision

## Engineering Infrastructure

* Automatic build system: `cmake`
* Version control: `git`
* Testing framework: `pytest`
* Documentation: GitHub `README.md`

## Schedule

Planning phase (6 weeks from 9/18 to 10/30): Setup the environment and get familiar with the algorithm

Week 1 (10/30): Implement the algorithm with C++

Week 2 (11/6): Make python wrappers for C++ with pybind

Week 3 (11/13): Finish C++, and start creating the interactive map in python

Week 4 (11/20): Implement features of the interactive map

Week 5 (11/27): Test all features with pytest

Week 6 (12/4): Finish up, debug, and write the documentation

Week 7 (12/11): Buffer time for further testing and debugging

Week 8 (12/18): Make slides and prepare for the presentation

## References

* [2D collision detection](https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection)
* [Quadtree collision detection optimization](https://davidhsu666.com/archives/quadtree_in_2d/#7-%E7%B8%BD%E7%B5%90)
