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

This is the psuedocode for image compression with quadtree:
```plaintext
function compressImage(image):
    if image is entirely the same color:
        return a single node with that color
    else:
        divide the image into 4 equal quadrants (top-left, top-right, bottom-left, bottom-right)
        topLeft = compressImage(top-left quadrant of image)
        topRight = compressImage(top-right quadrant of image)
        bottomLeft = compressImage(bottom-left quadrant of image)
        bottomRight = compressImage(bottom-right quadrant of image)
        return a new node representing the four children (topLeft, topRight, bottomLeft, bottomRight)

function decompressImage(node):
    if node is a leaf node:
        return a square or rectangle filled with the color of the leaf node
    else:
        reconstruct the image by combining the decompressed children:
        topLeftImage = decompressImage(node.topLeft)
        topRightImage = decompressImage(node.topRight)
        bottomLeftImage = decompressImage(node.bottomLeft)
        bottomRightImage = decompressImage(node.bottomRight)
        combine and return the four images to form the original image

# Example usage
originalImage = loadOriginalImage()
compressedImage = compressImage(originalImage)
reconstructedImage = decompressImage(compressedImage)
```

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
* `imageCompression(quadtree_data, style, depth)`: Compress the image using a specific style,
such as skeleton or cycle. Show the image compression process, and allow you to pause it 
as needed.
* `mouseRestoreImage(quadtree_data)`: Restore a specific part of the image compression by
left-clicking with the mouse.
* `mouseCompressImage(quadtree_data)`: Further compress a specific part of the image by 
right-clicking with the mouse.
* `exportImage(quadtree_data)`: Export the compressed image.
* `imageBenchmark()`: Display benchmark results to compare the size reduction and time 
consumption for the last compression.

C++ API:
* `imageCompression(quadtree_data, depth)`: Calculate image compression using a quadtree to
store image data.
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
