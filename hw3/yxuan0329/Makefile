CXX = g++
CFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3-config --includes`
CIMPORTPATH = includes/
LDFLAGS = -lblas

all: _matrix.so

_matrix.so: matrix.cpp TileHelper.cpp matrix_multi.cpp
		$(CXX) $^ $(CFLAGS) -I/usr/include/mk -I $(CIMPORTPATH) -o $@ ${LDFLAGS}

clean:
	rm -f *.so

test: _matrix.so
		python3 -m pytest test_matrix_multi.py -v

performance: _matrix.so
		python3 performance.py

.PHONY: all clean test 
