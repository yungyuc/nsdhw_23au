# WFCpp: <br>a Simple C++ Library for Wave Function Collapse

> [**WFCpp**][wfcpp-gh-repo] is a simple library for [Wave Function
> Collapse][wfc] implemented with modern C++ and also provides interfaces to
> Python with [pybind11][pybind11].


## Basic Information

- **Project Name**:
    WFCpp
- **GitHub Repository**:
    [https://github.com/Mibudin/wfcpp][wfcpp-gh-repo]
- **Languages**:
    C++, Python (with [pybind11][pybind11])

Procedural modeling of 2D textures or 3D models is a famous and popular topic
in the field of Computer Graphics. Among various techniques, [**Wave Function
Collapse**][wfc] is one of the most well-known algorithm, which majorly used
and popularized a previous academical work, [Model Synthesis][model-synthesis].
Please refer to Wave Function Collapse's [GitHub repository][model-synthesis]
where provides awesome description of this method. This algorithm has been used
by many game developers. By the way, it is originally a kind of 2D texture
synthesis techniques, but it can be also extended to 3D models[^3D-wfc-impl].

There is a long tradition of requiring "**local similarity**"[^local-similar]
when doing texture synthesis. Many algorithm of procedural modeling uses
"**grammar**"[^grammar] to produce models that are local similar to the input
one. Wave Function Collapse uses such grammars from the pixel/grid/tile-based
example to produce various results.


## Problem to Solve

The primary topic of Wave Function Collapse is to use the **grammar** with the
**pixel/grid/tile-based example** as the input and then iteratively generate
result graphics by **propagating** "waves" to analyze the possible results of
the remaining undetermined. The author called this concept as "minimal entropy
heuristic" way. This project needs to implement these essential functionalities
to make usage of the grammars and finally achieve the final goal.

Overall, there exist enormous and various implementing ways of Wave Function
Collapse which differ in detail of the implementation or use-customized
specifications in order that they can focus on different fields, such as
parallelization, result preferences, etc. Therefore, it is needed to determine
or select an appropriate implementation version among them.

Besides, this project has to provide friendly and widely flexible interfaces
between the C++ library and Python codes, to make this project easy to be used
in many kinds of applications.


## Prospective Users

The people who are interested or needed to use Wave Function Collapse as a
procedural modeling method to produce large-scale textures or models that are
local similar to given pixel/grid/tile-based examples. They may be artist,
designers, game developers, etc.


## API Description

> [!WARNING]
> The following API description only focuses on major exposed C++ API, which is
> brief and may not be the final version.

```cpp
/**
 * @brief The major WFC processor class
 */
class Model
{
public:
    /**
     * @brief Construct a new Model object
     * 
     * @param width the width of the result output
     * @param height the height of the result output
     * @param tiles the input tile-based example
     * @param grammar the grammar of production rules
     */
    Model(size_t width, size_t height, TileSet tiles, Grammar grammar);

    /**
     * @brief Initialize this Model
     */
    void init();

    /**
     * @brief Run the whole WFC algorithm iteratively
     * 
     * @param seed the random seed of this processing
     * @param limit the upper bound of the number of iterations
     */
    void run(int seed, int limit);

    /**
     * @brief Save the running result output to a file or a variable
     * 
     * @param path the path of the output file
     */
    void save(string path);
};
```


## Engineering Infrastructure

### C++-Python Interface

- [pybind11][pybind11]

### Automatic Build System

- [GNU Make][gnu-make]
- [CMake][cmake]

### Version Control

- [Git][git]
- [GitHub][github]

### Testing Framework

- [pytest][pytest]

### Continuous Integration

- [GitHub Actions][gh-actions]

### Documentation

- [Markdown files][gfm]
- [Doxygen-style documentation][doxygen-doc] (within C++ codes[^doc-comment])
- [Google-style docstring][google-docstring] (within Python
    codes[^doc-comment])


## Schedule

### Planning phase (6 weeks from 09/18 to 10/30)

- Study and research various versions of implementations of Wave Function
    Collapse, and select an appropriate one for this project
- Try to plan a detailed API specification
- Write the proposal

### Week 1 (10/30)

- Continuously try to plan a more concrete API specification
- Plan a concrete architecture of the codes about the whole processing
- Start to write the documents while developing

### Week 2 (11/06)

- Start to implement `Model`

### Week 3 (11/13)

- Implement `Model()`, `init()`
- Start to write testing code following the development

### Week 4 (11/20)

- Implement `run()`

### Week 5 (11/27)

- Implement `save()`

### Week 6 (12/04)

- Implement the interface to Python using `pybind11` 

### Week 7 (12/11)

- Try to develop a simple and minimal application using Wave Function Collapse

### Week 8 (12/18)

- Prepare the final presentation


## References

- Maxim Gumin. 2016.
    WaveFunctionCollapse.
    Retrieved from [https://github.com/mxgmn/WaveFunctionCollapse][wfc].
- Paul Merrell. 2007.
    Example-Based Model Synthesis.
    Symp. Interactive 3D Graphics and Games (2007), 105–112.
    Retrieved from [https://paulmerrell.org/model-synthesis/][model-synthesis].
- To be added...


<!-- Footnotes -->

[^3D-wfc-impl]:
    However, this project will only focus on 2D for the time being.
[^local-similar]: 
    The input and output are "locally similar". This means that every small 
    region within the output must match a small region in the input. But at the
    same time, their large-scale structure can be very different.
[^grammar]:
    A set of production rules that generates or modifies the result textures or 
    models.
[^doc-comment]:
    Documentation just by comment blocks beside the declarations.


<!-- Link Definitions -->

[wfcpp-gh-repo]:
    https://github.com/Mibudin/wfcpp
    "GitHub Repo: Mibudin/wfcpp"
[wfc]:
    https://github.com/mxgmn/WaveFunctionCollapse
    "GitHub Repo: mxgmn/WaveFunctionCollapse"
[model-synthesis]:
    https://paulmerrell.org/model-synthesis/
    "Model Synthesis Homepage"
[pybind11]:
    https://github.com/pybind/pybind11
    "GitHub Repo: pybind/pybind11"
[gnu-make]:
    https://www.gnu.org/software/make/
    "GNU Make Homepage"
[cmake]:
    https://cmake.org
    "CMake Homepage"
[git]:
    https://git-scm.com
    "Git Homepage"
[github]:
    https://github.com
    "GitHub Homepage"
[pytest]:
    https://docs.pytest.org
    "pytest Homepage"
[gh-actions]:
    https://github.com/features/actions
    "Features • GitHub Actions"
[gfm]:
    https://github.github.com/gfm/
    "GitHub Flavored Markdown Spec"
[doxygen-doc]:
    https://www.doxygen.nl/manual/docblocks.html
    "Doxygen Manual: Documenting the code"
[google-docstring]:
    https://google.github.io/styleguide/pyguide.html#381-docstrings
    "Google Python Style Guide: Docstring"
