CXX=g++
CXXFLAGS=-O3 -Wall -Wextra -shared -std=c++14 -fPIC -Wno-unused-function

PYBIND_INCLUDE=$(shell python3 -m pybind11 --includes)
PYINCLUDE=$(shell python3-config --includes)
TARGET=_matrix$(shell python3-config --extension-suffix)
NUMPYINCLUDE=$(shell python3 -c 'import numpy; print(numpy.get_include())')

MKL_INC=-I/usr/include/mkl
MKL_LIB=-L/usr/lib/x86_64-linux-gnu -lblas
IBLAS=-lblas
PYFLAGS=$(shell python3-config --ldflags)

.PHONY: main test clean

make: 
	$(CXX) $(CXXFLAGS) $(MKL_INC) $(PYINCLUDE) -I$(NUMPYINCLUDE) -I./ $(PYBIND_INCLUDE) ../mod.cpp -o $(TARGET) $(PYFLAGS) $(IBLAS)

test: main
	$(CXX) $(CXXFLAGS) $(MKL_INC) $(PYINCLUDE) -I$(NUMPYINCLUDE) -I./ $(PYBIND_INCLUDE) ../mod.cpp -o $(TARGET) $(PYFLAGS) $(IBLAS)
	../validate.py


clean:
	rm -rf *.so __pycache__ .pytest*
	cd ~/桌面/repo/nsdhw_23au/hw5
	rm -rf __pycache__ .pytest_cache

