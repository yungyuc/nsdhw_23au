# NSD Proposal

## Basic Information

I will implement conjugate gradient method as my final project.

Project URL: [https://github.com/ThreeMonth03/Conjugate-Gradient-Method-library](https://github.com/ThreeMonth03/Conjugate-Gradient-Method-library)


## Problem to Solve

I want to solve the global minima of the quadratic function by searching the numerical solution. One of the algorithm that can solve the problem is conjugate gradient method.

## Conjugate gradient method
### Introduction

Conjugate gradient method is a gradient-descent-based method that can find the minima of the quadratic function in the hyper-dimensional space. 

Given the quadratic function f(x):

$$\begin{aligned}
f(x) = \frac{1}{2}x^{T}Hx + b^{T}x + c
\end{aligned}
$$

The algorithm of conjugate gradient method can find 
$$ x_{min} = \underset{x}{\mathrm{argmin}} \quad f(x)$$

Compared with the steepest gradient method, the minima could be found in the finite step by conjugate gradient method in theory (if we don't consider the floating-point error and ill-conditioned), and the convergence iteration of conjugate gradient method is less than those of steepest gradient method.

### Algorithm
Given the function f(x):

$$\begin{aligned}
f(x) = \frac{1}{2}x^{T}Hx + b^{T}x + c
\end{aligned}
$$

And the algorithm is:



$$\begin{aligned}
& Input : Point_{initial}=x_{0} , Iteration = n,Coefficient = H, b  
\\\\& Initialize : s_{-1}= 0, \beta_{-1} = 1, g_{0} = g(x_{0}) = Hx_{0} + b, i = 0  
\\\\& While((i<n) \ and \ (x_{i} \neq x_{i-1})):  
\\\\& \quad \quad \quad \quad s_{i} = -g_{i} + \beta_{i-1}s_{i-1}  
\\\\& \quad \quad \quad \quad a_{i} = \frac{g_{i}^{T}s_{i}}{s_{i}^{T}Hs_{i}}  
\\\\& \quad \quad \quad \quad x_{i+1} = x_{i} + a_{i}s_{i}  
\\\\& \quad \quad \quad \quad g_{i+1} = g(x_{i}) = Hx_{i} + b  
\\\\& \quad \quad \quad \quad b_{i} = \frac{\lVert g_{i+1} \rVert^{2}}{\lVert g_{i} \rVert^{2}}  
\\\\& \quad \quad \quad \quad i = i+1  
\end{aligned}  
$$

## Prospective Users

Conjugate gradient method is pretty suitable for solving the regression problem. The algorithm can help the researchers working in deep learning, optimization and social science. 

## System Architecture

The above algorithm will be encapsulated by c++, and the algorithm also could be called by python with pybind11.

### Constraints

The system assumes that the input $H$ is positive-definite matrix and well-conditioned. 
The quadratic function exists a global minima if and only if the matrix $H$ is positive-definite. Additionally, the convergence speed is pretty fast only when $H$ is well-conditioned. 
In other words, people should check the constrain by themselves or numpy before using the project.

## API Description
The estimated API is below:
### c++
```c++
class ConjugateGradient: Algorithm{
    public:
        vector<double> const & H(vector<float> const & H) const;
        vector<double> & H(vector<float> & H);
        vector<double> const & b(vector<float> const & b) const;
        vector<double> & b(vector<float> & b);
        vector<double> find_minima(const int&& X0, const int&& epoch);
    private:
        vector<vector<double>> H;
        vector<double> B;
        int epoch;
        //....
};

```

### python 
The python API will call c++ API by pybind11, and the python API can accept the numpy format as input.

## Engineering Infrastructure

1. Documentation: README.md in Github Repository
2. Automatic build system: Makefile 
3. Version control: Git
4. Testing framework: Pytest
5. Wrapping: Pybind11

## Schedule

Week 1 (10/31): Implement the basic c++ API without multithread.

Week 2 (11/7):  Finish the basic c++ API without multithreading.

Week 3 (11/14): Wrapping and test for pytest.

Week 4 (11/21): Research how to dot product the matrix fastly.

Week 5 (11/28): Implement the matrix multiplication with multithread.

Week 6 (12/5): Prepare for the project oral report.

Week 7 (12/12): Flextime.

Week 8 (12/19): Flextime.

## References

1. Applied Numerical Analysis 7th, Curtis F. Gerald, Patrick O. Wheatley