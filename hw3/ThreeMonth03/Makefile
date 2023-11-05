CXX = g++
FLAGS = -O3 -g -m64 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
MKLINCLUDE = -I/usr/include/mkl
LIB_TARGET = _matrix.so
LBLS = -lblas

all: $(LIB_TARGET)
$(LIB_TARGET): _matrix.cpp
	$(CXX) $(MKLINCLUDE) $(FLAGS) $< -o $@ $(LBLS)

.PHONY: run test clean

test:
	python3 -m pytest -v test_matrix.py
	rm -f performance.txt
	python3 test_matrix.py | tee performance.txt

clean:
	rm -rf _matrix *.o *.so __pycache__ .pytest_cache