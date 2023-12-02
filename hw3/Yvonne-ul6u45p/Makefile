CXX = g++	# compiler
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC
PYFLAGS = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
# MKLROOT = /opt/intel/oneapi/mkl/2023.2.0
# MKL_INCLUDE = $(MKLROOT)/include
# MKL_LIB = $(MKLROOT)/lib/intel64
MKL_INCLUDE = /usr/include/mkl
MKL_LIB = /usr/lib/x86_64-linux-gnu/mkl
TARGET = _matrix.so
MAIN = matrixMultiply

all: $(TARGET)

$(TARGET): $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(PYFLAGS) $(MAIN).cpp -o $(TARGET) -L$(MKL_LIB) -I$(MKL_INCLUDE) -lblas

# $(MAIN): $(MAIN).cpp
# 	g++ -std=c++17 -O3 -Wall matrixMultiply.cpp -o matrixMultiply -L/opt/intel/oneapi/mkl/2023.2.0/lib/intel64 -I/opt/intel/oneapi/mkl/2023.2.0/include -lblas

.PHONY: test
test:
	make
	python3 -m pytest
	python3 benchmark.py
# make test should run the same unit tests.

.PHONY: clean
clean:
	rm -rf $(MAIN) *.o *.so .pytest_cache __pycache__
# make clean needs to remove all the built and intermediate files.
