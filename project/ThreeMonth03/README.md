Conjugate Gradient Method - A numerical method that can find the global minima 
of particular quadratic function
======

## Basic Information

I will implement conjugate gradient method as my final project.

Project URL:
[https://github.com/ThreeMonth03/Conjugate-Gradient-Method-library](
    https://github.com/ThreeMonth03/Conjugate-Gradient-Method-library)


## Problem to Solve

I want to solve the local minima of a function by searching the 
numerical solution. One of the algorithm that can solve the problem is 
conjugate gradient method.

## Conjugate gradient method
### Introduction

Conjugate gradient method is a numerical method that can find the 
minima of the function in the hyper-dimensional space, and conjugate gradient method includes linear conjugate method and non-linear conjugate method. 

Linear CG algorithm can precisely calculate the step length in every iteration,
but in order to calculate the precise step length, the objective function could
only be quadratic function. Compared with the steepest gradient method, the 
minima could be found in the 
finite step by conjugate gradient method in theory (if we don't consider the 
floating-point error and ill-conditioned), and the convergence iteration of 
conjugate gradient method is less than those of steepest gradient method.

Non-linear CG algorithm can approximately calculate the step length by line
search, or gradient descent method, and the advantage of non-linear CG 
algorithm is that the target function could be convex nonlinear objective 
functions.

### Algorithm

#### Linear conjugate gradient

Given the quadratic function f(x):

$$\begin{aligned}
f(x) = \frac{1}{2}x^{T}Hx + b^{T}x + c
\end{aligned}
$$

where $H$ is a positive-definite and symmetric matrix.  

And the algorithm is:

$$\begin{aligned}  
& Input : Point_{initial}=x_{0} , Iteration = n,Coefficient = H, b\\\\    
& Initialize : s_{-1}= 0, \beta_{-1} = 1, 
g_{0} = g(x_{0}) = Hx_{0} + b, i = 0\\\\   
& While((i \< n) \ and  \ (x_{i} \neq x_{i-1})):\\\\    
& \quad \quad \quad \quad s_{i} = -g_{i} + \beta_{i-1}s_{i-1}\\\\  
& \quad \quad \quad \quad a_{i} = \frac{g_{i}^{T}s_{i}}{s_{i}^{T}Hs_{i}}\\\\  
& \quad \quad \quad \quad x_{i+1} = x_{i} + a_{i}s_{i}\\\\  
& \quad \quad \quad \quad g_{i+1} = g(x_{i}) = Hx_{i} + b\\\\  
& \quad \quad \quad \quad b_{i} = \frac{\lVert g_{i+1} 
\rVert^{2}}{\lVert g_{i} \rVert^{2}}\\\\  
& \quad \quad \quad \quad i = i+1\\\\  
\end{aligned}  
$$

#### Non-linear conjugate gradient

![](https://i.imgur.com/wdRLKLl.png)

## Prospective Users

Conjugate gradient method is pretty suitable for solving the regression 
problem. The algorithm can help the researchers working in deep learning, 
optimization and social science. 

## System Architecture

The above algorithm will be encapsulated by c++, and the algorithm also could 
be called by python with pybind11.

### Constraints

The system assumes that the function exists a local minima.  
Thus, if people use the linear CG algorithm, the input $H$ is positive-definite and symmetric matrix.  

In other words, people should check the constraint by themselves or numpy 
before using the project.

For example, people could check whether $H$ is positive-definite by 
[yui's_nsd_project](https://github.com/yungyuc/nsdhw_23au/pull/98).

## API Description
The estimated API is below:
### c++
```c++
class LinearConjugateGradient: Algorithm{
    public:
        vector<double> const & H(vector<double> const & H) const;
        vector<double> & H(vector<double> & H);
        vector<double> const & b(vector<double> const & b) const;
        vector<double> & b(vector<double> & b);
        vector<double> find_minima(const double&& X0, const int&& epoch);
    private:
        vector<vector<double>> H;
        vector<double> B;
        int epoch;
        //....
};


class NonLinearConjugateGradient: Algorithm{
    public:
        vector<double> const & prev_point(vector<double> const & prev_point)
        const;
        vector<double> & prev_point(vector<double> & prev_point);
        vector<double> const & prev_grad(vector<double> const & prev_grad)
        const;
        vector<double> & prev_grad(vector<double> & prev_grad);
        vector<double> next_point(const double&& cur_point, const double&&
        cur_grad);
    private:
        vector<double> prev_point;
        vector<double> prev_grad;
        int epoch;
        //....
};
```

### python 
The python API will call c++ API by pybind11, and the python API can accept the
 numpy format as input.

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

Week 5 (11/28): Implement the matrix multiplication acceleration.

Week 6 (12/5): Implement the matrix multiplication acceleration.

Week 7 (12/12): Prepare for the project oral report.

Week 8 (12/19): Flextime.

## References

1. Applied Numerical Analysis 7th, Curtis F. Gerald, Patrick O. Wheatley  

2. [Introduction to Mathematical Optimization](
    https://indrag49.github.io/Numerical-Optimization/)