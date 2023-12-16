CXX = g++
FLAG = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
MKL_INCLUDE = /usr/include/mkl
MKL_LIB = /usr/lib/x86_64-linux-gnu/mkl

_matrix: mod.cpp
	$(CXX) $(FLAG) $< -o $@.so -L$(MKL_LIB) -I$(MKL_INCLUDE) -lblas

.PHONY: clean

clean: 
	rm -rf *.so .pytest_cache __pycache__ *.txt
