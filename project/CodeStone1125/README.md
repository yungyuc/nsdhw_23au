# Quadtreebased image compressor 
## Basic Information

A quadtree-based image compressor can reduce image sizes by 50% to 98%,
and you can adjust the compression level according to your preferences.

* github repository: [https://github.com/CodeStone1125/QuadraCompress](https://github.com/CodeStone1125/QuadraCompress)

## Problem to Solve

The primary objective of this system is to achieve a reduction in the
dimensions of images, rendering them suitable for diverse applications,
notably in the realm of image preprocessing essential for machine
learning model training. In comparative terms with other prevalent image
compression algorithms such as LZW and DCT, it is noteworthy that while
Quadtree may not stand out as the most robust solution, it unquestionably
distinguishes itself as the most adaptable and versatile choice.

### Quadtree
#### How do they work for image compression
First, let's briefly talk about how do Quadtrees work for image
compression. The algorithm for quadtree image compression involves producing
a new representation of an image based on the given image, a specified 
threshold, and the color information stored in the tree nodes. 
The key steps of the algorithm typically include: 
1. Start with the entire image as the root node of the quadtree.
2. Calculate the average color (usually RGB values) for the pixels within
    the current node.
3. Calculate the error or difference between the pixel colors and the
   average color within the node.
4. Compare the error with a predefined threshold. If the error is below the
   threshold, the node is considered a leaf node and does not get further subdivided.
5. If the error is above the threshold, the node is subdivided into four child
    nodes, and the process is recursively applied to each child node.
6. Continue the process until all leaf nodes are below the error threshold,
    effectively representing regions of the image where the colors are similar.

#### Why Quadtrees for image compression
Putting images into a tree data-structure is quite useful for many reasons. 
To start, they allow reducing the size of an image without necessarily 
reducing quality, as stated above in bold. This works best for images where 
similar colors take up a large portion of space like in the top left of the
image bellow where despite being many large subregions, they are hard to see.


| ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/b66ec4a2-0195-419f-b051-3b451d1347cc) | 
|:-----------------------------------:|
| **Quadtree sakura** |

Trees, including quadtrees, are known for expediting processes. Quadtrees 
specialize in focusing on the detailed sections of an image, particularly 
beneficial for speeding up edge detection. When performing edge detection 
on an image represented in a quadtree, we need to examine its leaf nodes and 
their parents.

Furthermore, quadtrees possess the unique ability to dynamically fine-tune 
image compression precision, delicately balancing the level of detail with
the consumption of computational resources. This adaptability is of paramount
importance, especially in resource-constrained domains such as IoT and machine
learning[1]. By elevating the threshold of the quadtree, we can craft images 
with reduced intricacy in less critical areas, thus conserving valuable computing
resources. Consequently, quadtrees emerge as invaluable assets in the realm of 
image compression.

### Why C++
The rationale behind implementing this project in C++ is primarily driven by 
the substantial computational demands.

As the number of iterations increases, the growth in the number of leaf nodes
within the Quadtree follows an exponential pattern. For each leaf node, we need
to calculate `node.error` using the following formula:

$$MSE = {Σ[(Ri - R {avg})^2 + (Gi - G_{avg})^2 + (Bi - B {avg} )^2] \over N}$$

Furthermore, within this [project](https://github.com/Inspiaaa/QuadTreeImageCompression#readme),
it is evident that if one seeks an image compression
that remains imperceptible to the human eye but reduces the file size significantly,
it necessitates approximately 80,000 iterations, taking roughly 21 seconds for each
image. I am confident that by implementing it in C++, I can enhance the acceleration
of this process.
| Original             | 80,000 Iterations          |
| -------------------- | -------------------------- |
| ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/0ca3fa48-ad67-4084-87db-f5c820720f32)| ![image](https://github.com/Inspiaaa/QuadTreeImageCompression/blob/master/docs/sunset_80000.jpg) |

## Prospective users

* Machine Learning developer: image compressor is an important step for image preprocess,
   It will accelerate the process of training model. And Quadtreebased image compressor
    can decide the degree of compression dynamiclly. Especially suitable for the device
  which need to strike ballence between speed and compution resources.

* videographer: For 3D animation creators, it is necessary to reduce precision in less
  critical areas, such as the background. This allows the animation to allocate computational
  resources to more important elements. Additionally, the quadtree's recursive image
  division characteristic imparts a distinct style, enabling artists to create unique
   works using quadtree image compression.
  
| ![image](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/bf6fb00a-38ab-4a33-b07a-215f85d6484e)|
|:-----------------------------------:|
| **Quadtree art** |
  

## System Architecture

|![SA2 drawio](https://github.com/CodeStone1125/nsdhw_23au/assets/72511296/b235b4d8-bfef-4f4d-9e9b-7225d1536116)|
|:-----------------------------------:|
| **System flow chart** |

## API Description

Python API:
* `imageLoader(input_image)`: Load user input image into quadtree
* `imageCompression(quadtree_data, style, threshold, depth)`: Compress the image with give
   a specific style, such as skeleton or cycle. Show the image compression process, and
  allow you to pause it as needed.
* `mouseRestoreImage(quadtree_data)`: Restore a specific part of the image compression by
left-clicking with the mouse.
* `mouseCompressImage(quadtree_data)`: Further compress a specific part of the image by 
right-clicking with the mouse.
* `exportImage(quadtree_data)`: Export the compressed image.
* `imageBenchmark()`: Display benchmark results to compare the size reduction and time 
consumption for the last compression.

C++ API:
* `imageCompression(quadtree_data, threshold , depth)`: Calculate image compression with given threshold
   and using a quadtree to store image information.
* `restoreImage(quadtree_data, restorationLevel, algorithm)`: Restore image compression.
* `quadtree(input_image)`: Implementation of the quadtree data structure.
  *  `__init__(self, position, size, subdivided_flags, colors) `
  *  `_create_child_node(self, position, size) `


## Engineering Infrastructure
* Automatic build system: `cmake`
* Version control: `git`
* Testing framework: `pytest`
* Documentation: GitHub `README.md`

## Schedule

Planning phase (6 weeks from 9/18 to 10/30): Think up presentation, then set up the environment
and get familiar with the algorithm

Week 1 (10/30): Write pytest, make file and implement the algorithm with C++ 

Week 2 (11/6): continously implement the algorithm with C++ and make python wrappers for C++ with pybind

Week 3 (11/13): Finish C++, and start creating the interactive GUI in python

Week 4 (11/20): Implement features of the interactive GUI

Week 5 (11/27): Test all features with pytest

Week 6 (12/4): Finish up, debug, and write the documentation

Week 7 (12/11): Buffer time for further testing and debugging

Week 8 (12/18): Make slides for the presentation

## References

* [QuadTreeImageCompression](https://github.com/Inspiaaa/QuadTreeImageCompression)
* [Probabilistic Approach Versus Machine Learning for One-Shot Quad-Tree Prediction in an Intra HEVC Encoder](https://link.springer.com/article/10.1007/s11265-018-1426-z)

[1]
Shenchang Eric Chen and Lance Williams. 2023. View Interpolation for Image Synthesis. Seminal Graphics Papers: Pushing the Boundaries, Volume 2 2, 45 (August 2023), 423-432. DOI:https://doi.org/10.1145/3596711.3596757
