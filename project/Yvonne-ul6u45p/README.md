# Contiguous Array adding Multi-Dimensional Index Calculation


## Basic Information

Multi-dimensional arrays of fundamental types and struct are a building block
for numerical code. It may be as simple as a pointer to a contiguous memory
buffer, or well-designed meta-data with the memory buffer.

- My GitHub Repository:
    https://github.com/Yvonne-ul6u45p/ContiguousArray-MultiDim-Index-Calculation


## Problem to Solve

While a mere pointer works well with one-dimensional arrays, calculating the
pointer offset for multi-dimensional arrays makes the code for numerical
calculation cryptic and hard to maintain. It is very helpful to wrap the multi-
dimensional index calculation in a library.


## Prospective Users

This project targets users who search for an easy-handle multi-dimensional
matrix calculation using contiguous array.


## System Architecture

### Calculations

1. Matrix-Matrix Multiplication on Multi-Dimension
1. Matrix-Matrix Multiplication with tiling on Multi-Dimension
1. Vector-Matrix Multiplication on Multi-Dimension
1. Element-wise Matrix Multiplication on Multi-Dimension 
1. Linear Self-Covariance Matrix on Multi-Dimensional 
<!-- Add Formula -->

* Additionl Function: add variables for specifying dimension


## API Description

### C++

#### Fundamental Types

<!-- >> Using cblas_dgemm or not? -->
```C++
// Naive matrix-matrix multiplication.
Matrix operator* (Matrix const & mat1, Matrix const & mat2)
{
    // ...
}

// Tiled matrix-matrix multiplication.
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t const tsize)
{
    // ...
}

// Vector-Matrix multiplication.
Matrix operator* (Matrix const & mat, std::vector<double> const & vec)
{
    // ...
}

// Element-wise Matrix Multiplication
Matrix elem_multiply(Matrix const & mat1, Matrix const & mat2)
{
    // ...
}

// Linear Self-Covariance Matrix Multiplication
Matrix linear_CovMat(Matrix const & mat1)
{
    // ...
}

```


#### Composite Types (struct)

```C++
struct Matrix
{
    public:

        Matrix(std::vector<size_t>);
        Matrix(std::vector<size_t>, std::vector<double> const & vec);
        Matrix & operator=(std::vector<double> const & vec)
        Matrix(Matrix const & other);
        Matrix & operator=(Matrix const & other);
        Matrix(Matrix && other);
        Matrix & operator=(Matrix && other);
        ~Matrix();
        double   operator() (std::vector<size_t>) const;
        double & operator() (std::vector<size_t>);
        bool operator== (Matrix const & mat2);
        bool operator!= (Matrix const & mat2);
        size_t dim(size_t d) const;
        size_t size() const;
        double  buffer(size_t i) const;
        std::vector<double> buffer_vector() const;

        // Naive matrix-matrix multiplication.
        Matrix operator@ (Matrix const & other);
        // Vector-Matrix multiplication.
        Matrix operator@ (std::vector<double> const & vec);
        // Tiled matrix-matrix multiplication.
        Matrix multiply_tile(Matrix const & other, size_t const tsize);
        // Element-wise Matrix Multiplication
        Matrix operator* (Matrix const & other);        // element-wise multiplication
        // Linear Self-Covariance Matrix Multiplication
        Matrix Cov();
    
    private:

        size_t index(size_t row, size_t col) const;
        void reset_buffer(size_t nrow, size_t ncol);
        size_t m_nrow = 0;
        size_t m_ncol = 0;
        double * m_buffer = nullptr;
};
```

* The C++ user can link the library by compiling with:
    `g++ main.cpp -o -lcontiguous_matrix_calculate`

### Python
* The python API can accept the numpy ndarray format as inputs, and call C++
    API using pybind11.
* Users can use the library by adding:
    `import contiguous_matrix_calculate`


### Overall Architecture

```mermaid
```

## Engineering Infrastructure

1. Automatic build system: 
    - `CMake`
2. Version control:
    - `git`
3. Testing framework:
    - `pytest`
4. Documentation:
    - `Markdown`
5. Continuous Integration: 
    - Github Actions


## Schedule

* Write down encountered issues as much as possible.

* Week 1 (11/12):
    - Write `pytest`
    - Write Continuous Integration
* Week 2 (11/19):
    - C++: Implement *Element-wise Matrix Multiplication* in fundamental types
* Week 3 (11/26):
    - C++: Implement *Linear Self-Covariance Matrix Multiplication* in
            fundamental types
* Week 4 (12/03):
    - C++: Implement *composite types (struct)*
* Week 5 (12/10):
    - wrap up with `pybind`
    - Write Python API
* Week 6 (12/17):
    - Measure Performance, including runtime and memory consumption
    - write automatic build system by `Cmake`
* Week 7 (12/23):
    - Make Slides
    - Prepare for the presentation


## References

1. [contiguous container library - arrays](https://github.com/foonathan/array)
2. [contiguous array type](https://github.com/andrewthad/contiguous)
