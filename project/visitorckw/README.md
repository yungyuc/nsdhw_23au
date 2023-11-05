# Runtime Profile-Guided Optimization Sorting Library
## Basic Information

Sorting algorithms are a fundamental component of numerical software, frequently employed
for the purpose of organizing data efficiently. Speed is often a critical concern when it
comes to sorting, but the optimal sorting algorithm can vary widely depending on the
specific context. For instance, when sorting an array on most processors, quicksort is a
popular choice due to its high cache hit rate and minimal element comparison counts,
resulting in excellent performance. However, in certain applications, such as embedded
systems like the Linux kernel, where memory is scarce and precious, quicksort's use of
additional stack space for recursion (resulting in an additional O(log(N)) space usage)
makes it unacceptable. As a result, the Linux kernel employs heapsort for array sorting.
When dealing with linked lists instead of arrays, quicksort and heapsort are rarely used
since linked lists lack random access support. In such cases, mergesort is a more commonly
utilized sorting algorithm. However, mergesort's requirement of O(N) additional space when
sorting an array often makes it slower in practice compared to quicksort. Furthermore, the
degree of local data ordering can significantly impact sorting speed. Therefore, hybrid
sorting algorithms like Timsort are better suited to handle locally ordered data.
Additionally, some platforms, like x86, offer support for SIMD (Single Instruction, Multiple
Data) instructions, enabling the development of specialized SIMD sorting algorithms for
improved efficiency. Given the diverse sorting needs across different scenarios, we aim to
provide an API that allows users to supply real-world test data for the library to
automatically select the most suitable sorting method. Furthermore, we hope to enhance
existing sorting implementations in libraries like NumPy or the Linux kernel through
techniques such as cache optimization and SIMD utilization.

## Problem to Solve

The primary goal of this project is to develop a versatile sorting library that leverages
runtime profile-guided optimization techniques to automatically select the most appropriate
sorting algorithm based on the characteristics of the input data. The library should also
explore methods to optimize existing sorting implementations in widely-used software, such
as NumPy and the Linux kernel, to improve their overall performance and efficiency.

## Prospective users

The Runtime Profile-Guided Optimization Sorting Library is designed to benefit a wide range
of users and applications within the field of numerical software development. Potential
users and beneficiaries of this library include, but are not limited to:

1. Software Developers:

Numerical software developers who need efficient and adaptive sorting algorithms in their
applications. Developers working on projects involving data analysis, scientific computing,
or data manipulation.

2. Data Scientists:

Professionals and researchers in the data science and analytics domains who frequently deal
with large datasets. Users of libraries like NumPy in the Python ecosystem who seek
enhanced sorting performance.

3. Embedded System Programmers:

Developers working on resource-constrained platforms, such as embedded systems,
microcontrollers, and IoT devices, where memory usage and sorting efficiency are critical.

4. Linux Kernel Developers:

Contributors and maintainers of the Linux kernel who require sorting capabilities within
the kernel, particularly for tasks like process scheduling and file system management.

5. Performance Optimizers:

Individuals focused on optimizing the performance of numerical software, whether for
research purposes or to enhance the efficiency of existing codebases.

6. Open Source Community:

The open-source software community at large, which can benefit from the availability of a
high-quality sorting library with runtime profiling and optimization capabilities.

7. Educational Institutions:

Professors, students, and educational institutions teaching courses related to data
structures, algorithms, and numerical computing, as this library can serve as an educational
resource.

8. Developers in HPC (High-Performance Computing):

Professionals in the field of high-performance computing who need efficient sorting
solutions for tasks like simulation, modeling, and scientific research.
  

## System Architecture

The Runtime Profile-Guided Optimization Sorting Library is designed with a flexible and
extensible system architecture to provide efficient sorting solutions for both arrays and
linked lists. It offers a range of sorting algorithms, allowing users to select the most
suitable method based on their specific needs. The system architecture includes the
following key components and functionalities:

### Data Structures:

- Array: The library supports sorting of arrays, and users are required to specify the size
of each element to enable correct sorting. The provided array can be of any data type.
- Linked List: For linked list sorting, a C++ class follows Linux kernel-style coding
conventions to encapsulate the linked list structure, making it convenient and user-friendly.

### Sorting Methods:

The library offers a selection of sorting methods, which are defined using an enum called
SortingMethod. These methods include:
- QUICKSORT
- MERGESORT
- HEAPSORT
- BINARY_INSERTION_SORT
- TIMSORT
- INTROSORT

### Functionality:

- Recommend Sorting Method: The library provides a function that takes test data and a
memory limit as input and recommends the most suitable sorting method based on the
characteristics of the data and memory constraints.
- Sorting Functions: Users can invoke sorting functions for both arrays and linked lists,
specifying the sorting method they wish to use.
- Performance Measurement: The library includes functions to measure the execution time,
comparison counts, and swap counts for a given sorting task.
- Result Visualization: A function is available to create graphs that visualize the results
of performance tests.


This system architecture allows for easy integration of various sorting algorithms and
provides a user-friendly interface for developers working with different data structures.
The ability to recommend sorting methods based on data characteristics enhances the
adaptability of the library, ensuring that users can choose the most efficient sorting
approach for their specific use cases. The modular structure of the library facilitates
future extensions and the addition of new sorting methods or optimizations as needed.

## API Description
C++ API:
* `enum SortingMethod { QUICKSORT, MERGESORT, HEAPSORT, BINARY_INSERTION_SORT, TIMSORT, INTROSORT };`
* `SortingMethod RecommendSortingMethod(const std::vector<T>& data, size_t memoryLimit);`
* `void SortArray(std::vector<int>& data, SortingMethod method);`
* `void SortLinkedList(struct list_head* head, SortingMethod method);`
* `void MeasureSortingPerformance(const std::vector<T>& data, SortingMethod method, double& executionTime, size_t& comparisons, size_t& swaps);`
* `void PlotTestResults(const std::vector<double>& executionTimes, const std::vector<size_t>& comparisons, const std::vector<size_t>& swaps);`

## Engineering Infrastructure
* Automatic build system: `make`
* Version control: `git`
* Testing framework: `pytest`
* Documentation: GitHub `README.md`


## Schedule

Planning phase (6 weeks from 9/18 to 10/30): Think up presentation, then set up the environment
and get familiar with the algorithm

Week 1 (10/30):  Project Initiation

- Define project objectives, scope, and requirements.
- Set up the development environment and tools.
- Create a project plan, including milestones and deliverables.

Week 2 (11/6): Data Structures and API Design

- Design the data structures for arrays and linked lists.
- Develop the initial version of the SortingLibrary class.
- Define the SortingMethod enum and sorting functions.

Week 3 (11/13): Implement Sorting Algorithms

- Implement the basic sorting algorithms for arrays and linked lists.
- Test the sorting algorithms with sample data.

Week 4 (11/20): Recommendation Functionality

- Implement the RecommendSortingMethod function to suggest sorting methods based on data and memory constraints.
- Test the recommendation functionality with various data scenarios.

Week 5 (11/27): Sort and Measure Performance

- Complete the SortArray and SortLinkedList functions for specified sorting methods.
- Implement the MeasureSortingPerformance function to capture execution time, comparisons, and swaps.
- Verify sorting performance and measurement accuracy.

Week 6 (12/4): Result Visualization

- Develop the PlotTestResults function to generate performance test result visualizations.
- Create sample test cases and visualize the results.
- Enhance the user interface for ease of use.

Week 7 (12/11): Testing and Debugging

- Conduct extensive testing of the entire library, addressing any bugs and performance issues.
- Optimize and refine the code for efficiency and correctness.

Week 8 (12/18): Documentation and Finalization

- Create comprehensive documentation, including a user guide and API reference.
- Finalize the project by ensuring that all functionalities meet the project objectives.
- Prepare for project submission and presentation.

## References

- Bottom-up Mergesort: A Detailed Analysis
  Wolfgang Panny, Helmut Prodinger
  Algorithmica 14(4):340--354, October 1995
  https://doi.org/10.1007/BF01294131
  https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.6.5260
- The cost distribution of queue-mergesort, optimal mergesorts, and
  power-of-two rules
  Wei-Mei Chen, Hsien-Kuei Hwang, Gen-Huey Chen
  Journal of Algorithms 30(2); Pages 423--448, February 1999
  https://doi.org/10.1006/jagm.1998.0986
  https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.4.5380
- Queue-Mergesort
  Mordecai J. Golin, Robert Sedgewick
  Information Processing Letters, 48(5):253--259, 10 December 1993
  https://doi.org/10.1016/0020-0190(93)90088-q
  https://sci-hub.tw/10.1016/0020-0190(93)90088-Q
- BOTTOM-UP-HEAPSORT, a new variant of HEAPSORT beating, on an average,
  QUICKSORT (if n is not very small)
  Ingo Wegener
  https://doi.org/10.1016/0304-3975(93)90364-Y
- Linux Kernel Library: list_sort
  https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/lib/list_sort.c
- Linux Kernel Library: sort
  https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/lib/sort.c
- Numpy sort implementation
  https://github.com/numpy/numpy/tree/main/numpy/_core/src/npysort
- Intel x86-simd-sort
  https://github.com/intel/x86-simd-sort/tree/main
- Cpython listsort.txt
  https://github.com/python/cpython/blob/main/Objects/listsort.txt
