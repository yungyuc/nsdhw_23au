CC = g++
CFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
MKLINCLUDE = -I/usr/include/mkl
PYINCLUDE = $(shell python3-config --includes)  $(shell python3 -m pybind11 --includes)
PYINCLUDE += $(shell python3 -c "import numpy; print('-I' + numpy.get_include())")
PYESUFFIX = $(shell python3-config --extension-suffix)
LIBS = -lblas
PYTHON = python3
TARGET=_matrix$(PYESUFFIX)

all: $(TARGET)

$(TARGET): mod.o matrix.o
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< $(PYINCLUDE) $(MKLINCLUDE) -o $@

# _matrix.o: _matrix.cpp _matrix.hpp
# 	$(CC) $(CFLAGS) -c _matrix.cpp $(MKLINCLUDE)

.PHONY: test clean
test: $(TARGET)
	$(PYTHON) test.py

clean:
	rm -f *.o *.so *.pyc