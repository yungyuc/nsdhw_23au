CXX = g++
CFLAGS = -O3 -Wall -shared -std=c++17 -fPIC 
COMPILE_SOURCE = matrix.cpp
OBJECT = -o _matrix

MKL_INCLUDE = -I/usr/include/mkl
MKL_LIBRARY = -L/usr/lib/x86_64-linux-gnu/ -lblas

PYTHON_CONFIG = $(shell python3-config --extension-suffix)
PYTHON_INCLUDE = $(shell python3-config --includes)
PYBIND_INCLUDE = $(shell python3 -m pybind11 --includes)




all: matrix.cpp
	$(CXX) $(CFLAGS) $(PYBIND_INCLUDE) $(COMPILE_SOURCE) $(OBJECT)$(PYTHON_CONFIG) $(PYTHON_INCLUDE) $(MKL_LIBRARY) $(MKL_INCLUDE)


.PHONY: clean
clean:
	rm -rf *.so