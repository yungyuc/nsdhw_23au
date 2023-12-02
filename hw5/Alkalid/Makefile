CXX = g++
CFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
INCLUDE := $(shell python3 -m pybind11 --includes)
CONFIG := $(shell python3-config --extension-suffix)
PY := $(shell python3-config --includes)
MKL_INC = -I/usr/include/mkl
MKL_LIB = -lblas
SRC= ../mod.cpp


all: _matrix$(CONFIG)

_matrix$(CONFIG): $(SRC)
	$(CXX) $(CFLAGS) -I./ $(MKL_INC) $(PY) $(INCLUDE) $^ -o $@ $(MKL_LIB)


test: all
	python3 -m pytest

clean:
	rm -rf __pycache__ .pytest_cache _matrix*.so
