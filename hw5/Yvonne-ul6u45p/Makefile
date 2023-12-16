CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC
PYTHONFLAGS = `python3-config --includes --ldflags` `python3 -m pybind11 --includes`
# MKLROOT = /opt/intel/oneapi/mkl/2023.2.0
# MKL_INCLUDE = $(MKLROOT)/include
# MKL_LIB = $(MKLROOT)/lib/intel64
MKL_INCLUDE = /usr/include/mkl
MKL_LIB = /usr/lib/x86_64-linux-gnu/mkl
NUMPYINCLUDE = `python3 -c 'import numpy; print(numpy.get_include())'`

_matrix: ../mod.cpp
	$(CXX) $(CXXFLAGS) $(PYTHONFLAGS) $< -o $@.so -I. -I$(NUMPYINCLUDE) -L$(MKL_LIB) -I$(MKL_INCLUDE) -lblas

.PHONY: clean
clean:
	rm -rf *.so .pytest_cache __pycache__
