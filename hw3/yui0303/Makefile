# Write a Makefile of using g++ to compile Matrix.cpp, Matrix.hpp _matrix.cpp
CC = g++
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC
MKLINCLUDE = -I/usr/include/mkl 
PYINCLUDE = $(shell python3-config --includes)  $(shell python3 -m pybind11 --includes)
PYESUFFIX = $(shell python3-config --extension-suffix)
PYTHON = python3
TARGET=_matrix$(PYESUFFIX)
LIBS = -lblas

all: $(TARGET)

$(TARGET): _matrix.o
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)

_matrix.o: _matrix.cpp _matrix.hpp
	$(CC) $(CFLAGS) -c _matrix.cpp $(MKLINCLUDE) $(PYINCLUDE)

.PHONY: test
test: $(TARGET)
	$(PYTHON) -m pytest -v test_matrix.py
	rm performance.txt
	$(PYTHON) test_matrix.py | tee performance.txt
	echo "==================== environment ====================" >> performance.txt
	lscpu >> performance.txt

.PHONY: clean
clean:
	rm -rf _matrix *.o *.so __pycache__ .pytest_cache
