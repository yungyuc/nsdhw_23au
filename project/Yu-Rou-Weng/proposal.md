# Mesh Data Converter: A Simple C++ Libaray to Convert NASA's Plot3D to SU2


## Basic Information

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

* Github Repository: [https://github.com/Yu-Rou-Weng/Mesh-Data-Converter/tree/master](https://github.com/Yu-Rou-Weng/Mesh-Data-Converter/tree/master)

## Problem to Solve

Plot3D and SU2 serve as good examples of the numerical analytical codes:

1. Plot3D is a file format which can only store structured grid and result data and 
  remains a only file format in the filed of Computaional Fluid Dynamic (CFD).

2. SU2 is a suite of open-source software tools written in C++ for the numerical solution 
  of partial differential equations (PDE) and performing PDE-constrained optimization.

When dealing with numerical analysis, the mesh data format differs between Plot3D and SU2. 
Plot3D uses structured mesh as input, while SU2 uses unstructured mesh for solving fluid dynamics.

The goal of this project is to create a file format converter that can translate Plot3D mesh data 
into a format compatible with SU2. This converter will function as a standalone executable, facilitating data exchange between different programs. Also, the converter will be integrated to [modmesh](https://github.com/solvcon/modmesh) to serve as a useful plugged-in library for easier automation.

## Prospective Users

1. [modmesh](https://github.com/solvcon/modmesh):  
     - modmesh is a toolkit for solving Partial Differential Equations (PDE)  
     - Fluid flow problems in Computational Fluid Dynamics (CFD) are often   
     described by PDE
     - modmesh converts geometric information into computer-readable formats like Plot3D.
     This converter facilitates seamless integration between modmesh and SU2, enabling 
     accurate and efficient computational fluid dynamics simulations

2. Fluid dynamics professionals or researchers who need to exchange mesh data between Plot3D and SU2 when using different simulation software.

3. In the aerospace and automotive industries, engineers frequently rely on computational fluid dynamics (CFD) simulations. This converter offers a more precise mesh data conversion solution 
for their simulations.

4. Computer scientists, students, and educators who are working in computational fluid dynamics studies and experiments.

## System Architecture

![image](https://github.com/Yu-Rou-Weng/nsdhw_23au/blob/Yu-Rou-Weng-Proposal-Submission/project/Yu-Rou-Weng/image/ConceptFlowChart.png)

## API Description

1. Fuctions in c++ will include ReadPlot3DData, WriteSU2Data, ConvertPlot3DToSU2
   - Use Python to read input and write output data
   - Use C++ to implement the `Data Conversion` library

2. Use Pybind11 to wrap C++ functions for Python

## Engineering Infrastructure

1. Automatic build system: `CMake`
2. Version control: `Git`
3. Testing framework: `Pytest`
4. Documentation: `README`, [`PyDoc`](https://marketplace.visualstudio.com/items?itemName=njpwerner.autodocstring)

## Schedule

* Week 1 (10/30):  
     - Study domain knwoledges and meanwhile write corresponding prototypes
     - Prepare a presentaion skeleton  
* Week 2 (11/6):  
     - Search and gather suitable Plot3D mesh data format and comprehend structures and characteristic of both Plot3D and SU2  
     - Start to design the conversion in C++ if 1. is done in advance
* Week 3 (11/13):  
     - Implement conversion in C++ & write pybind11 wrapper
* Week 4 (11/20):  
     - Implement conversion in C++ & write pybind11 wrapper
* Week 5 (11/27):  
     - Implement a CMake file for a draft  
     - Add some works and adjust the presentation draft
* Week 6 (12/4):  
     - Write unit tests and refactor codes  
     - Check whether if my presentation draft follow the grading criteria  
     - Integrate to modmesh (depends on remaining time)
* Week 7 (12/11):  
     - Buffer time for debugging and documentation
* Week 8 (12/18):  
     - Refine and finish the final project, prepare for the presentation

## References

- [Plot3D Documentation](https://nasa.github.io/Plot3D_utilities/_build/html/)
- [Plot3d File Format for Grid and Solution Files](https://www.grc.nasa.gov/www/wind/valid/plot3d.html)
- [SU2](https://su2code.github.io/)
- To be added…
