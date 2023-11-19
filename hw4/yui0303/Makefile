CC = g++
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC
MKLINCLUDE = -I/usr/include/mkl
PYINCLUDE = $(shell python3-config --includes)  $(shell python3 -m pybind11 --includes)
PYESUFFIX = $(shell python3-config --extension-suffix)
LIBS = -lblas
PYTHON = python3
TARGET=_matrix$(PYESUFFIX)

all: $(TARGET)

$(TARGET): pybind.o _matrix.o
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)

pybind.o: pybind.cpp
	$(CC) $(CFLAGS) -c pybind.cpp $(MKLINCLUDE) $(PYINCLUDE)

_matrix.o: _matrix.cpp _matrix.hpp _allocator.hpp
	$(CC) $(CFLAGS) -c _matrix.cpp $(MKLINCLUDE)

.PHONY: test clean
test: $(TARGET)
	$(PYTHON) test.py

clean:
	rm -f *.o *.so *.pyc