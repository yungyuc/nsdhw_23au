# Quadtreebased image compressior 
## Basic Information

A quadtree-based image compressor can reduce image sizes by 50% to 98%, and you can
adjust the compression level according to your preferences.

* github repository: [https://github.com/CodeStone1125/QuadraCompress](https://github.com/CodeStone1125/QuadraCompress)

## Problem to Solve

The primary objective of this system is to achieve a reduction in the
dimensions of images, rendering them suitable for diverse applications,
notably in the realm of image preprocessing essential for machine
learning model training. In comparative terms with other prevalent image
compression algorithms such as LZW and DCT, it is noteworthy that while
Quadtree may not stand out as the most robust solution, it unquestionably
distinguishes itself as the most adaptable and versatile choice.

### Why Quadtree
Also, Based on this [paper](https://dl.acm.org/doi/abs/10.1145/3596711.3596757?casa_token=o3_5H2E-d54AAAAA:5bq5xqCI0KOk7pc1DSMh0CkpyNuXtkO6h9HUTdQpnDCodGOtd1h1EF8NAUJIQtfKZUP84FTbNeEjgA)
Quadtree have sevral advantage on image process.
1. Scene Simplification: Quadtree allows for the partitioning of images
 into smaller blocks or regions, reducing the image's resolution levels.
  This simplification is particularly beneficial for image compression
   and analysis tasks.

2. Efficiency: Quadtree technology provides a hierarchical representation
  of image data. This enables selective processing of specific regions
   of interest within an image. The result is significantly improved
    processing efficiency, which is especially valuable for applications
 requiring the rapid processing of large images or video streams.

3. Automatic Correspondence: Quadtree decomposition can automatically
 establish correspondence between images, a critical factor in various
  image processing and matching tasks. This reduces the need for manual
   intervention and streamlines the processing workflow.

4. Adaptability: Quadtree decomposition divides images based on their unique
    characteristics.This adaptability allows different regions of an image
   to be processed at varying resolutions, making image processing more
   intelligent and resource-efficient.

5. Resource Management: Quadtree technology plays a vital role in efficient
    resource management for image data. This includes optimizing storage and
    transmission, which is particularly advantageous for mobile applications
    and environments with limited resources.

In summary, quadtree technology simplifies image organization, enhances processing 
efficiency, automates correspondence tasks, adapts to various image characteristics,
and efficiently manages image resources in the field of image processing.
| ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/75069f10-594b-40b4-8407-5b047b39980c) | ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/74d93574-06db-40ad-88f3-a2e1fdcbcd5b) |
|:-----------------------------------:|:-----------------------------------:|
| **Quadtree Simpson** |**Quadtree rabbit**|

### Why C++
The rationale behind implementing this project in C++ is primarily driven by 
the substantial computational demands.

As the number of iterations increases, the growth in the number of blocks within the
Quadtree follows an exponential pattern. Additionally, I aspire for my compressor to
have the capability to dynamically adjust compression levels in real-time to cater to
specific needs, which itself constitutes a computational challenge.

Furthermore, within this project, it is evident that if one seeks an image compression
that remains imperceptible to the human eye but reduces the file size significantly,
it necessitates approximately 80,000 iterations, taking roughly 25 seconds for each
image. I am confident that by implementing it in C++, I can enhance the acceleration
of this process.
| Original             | 80,000 Iterations          |
| -------------------- | -------------------------- |
| ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/0ca3fa48-ad67-4084-87db-f5c820720f32)| ![image](https://github.com/Inspiaaa/QuadTreeImageCompression/blob/master/docs/sunset_80000.jpg) |

## Prospective users

* Game Developer: Determine whether something in a game world is attach by a character is very
  common in game developing. There are even games making this as one of their main features, like
  [Super Mario](https://zh.wikipedia.org/zh-tw/%E8%B6%85%E7%BA%A7%E9%A9%AC%E5%8A%9B%E6%AC%A7%E7%B3%BB%E5%88%97)
  and [Pokemon](https://zh.wikipedia.org/wiki/%E5%AE%9D%E5%8F%AF%E6%A2%A6%E7%B3%BB%E5%88%97#%E9%81%8A%E6%88%B2)

| ![Mario](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/6cc86227-9b61-4cf0-9512-57dde95d2282) | ![pokemon](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/4b122746-9e38-4540-8df4-942cec57d56d) |
|:-----------------------------------:|:-----------------------------------:|
| **Super Mario** |**Pokemon**|



* Collision Prevention for Automation Equipment: Robots and automation devices used in industrial
   automation need to ensure that they do not collide or interfere with each other while
   performing tasks.2D collision detection can monitor the positions of individual machine
   components to prevent unnecessary collisions, enhance production efficiency, and safeguard equipment.

## System Architecture




| ![system_architechture](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/a1b2b43a-7a16-47a2-9ca2-afd4858d5c79) |
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
