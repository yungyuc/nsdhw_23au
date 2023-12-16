CXX=g++
CXXFLAGS = -O3 -Wall -shared -fPIC -std=c++17 -I./
PYBIND=`python3 -m pybind11 --includes`
PYCONFIG=`python3-config --extension-suffix`
NUMPY_INCLUDE=$(shell python3 -c "import numpy; print(numpy.get_include())")

MKLROOT=/usr/lib/x86_64-linux-gnu
LDFLAGS=-L${MKLROOT} \
	-lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 \
	-lpthread -lm -ldl

all: matrix.hpp ../mod.cpp
	$(CXX) $(CXXFLAGS) -I$(MKLROOT) $(PYBIND) $(shell python3-config --includes --ldflags) ../mod.cpp -o _matrix$(PYCONFIG) -I$(NUMPY_INCLUDE) $(LDFLAGS)
.PHONY: all

test: all
	python3 -m pytest -v -s
.PHONY: test

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/
.PHONY: clean