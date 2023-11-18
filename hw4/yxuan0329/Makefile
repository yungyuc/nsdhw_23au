CXX = g++
CFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3-config --includes`
CIMPORTPATH = includes/
LDFLAGS = -lblas

all: _matrix.so

_matrix.so: matrix.cpp
		$(CXX) $^ $(CFLAGS) -I/usr/include/mk -I $(CIMPORTPATH) -o $@ ${LDFLAGS}

clean:
	rm -f *.so

.PHONY: all clean test 
