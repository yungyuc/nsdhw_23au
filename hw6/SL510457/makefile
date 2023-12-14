CC = g++
MKLINCLUDE = -I/usr/include/mkl
INCLUDE = `python3 -m pybind11 --includes`
POSFIX = `python3-config --extension-suffix`
CONFIG = `python3-config --includes`
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

.PHONY: all, matrix, clean 

all: matrix 

matrix: _matrix.cpp
	$(CC)  $(CFLAGS) $(INCLUDE) _matrix.cpp -o _matrix$(POSFIX)  -lblas $(MKLINCLUDE) $(CONFIG) 


clean:
	rm -f *.so 
	rm -rf __pycache* .pytest*