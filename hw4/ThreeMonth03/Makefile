CXX = g++
FLAGS = -O3 -g -m64 -Wall -shared -std=c++11 -fPIC 
MKLINCLUDE = -I/usr/include/mkl
LIB_SHARE_OBJS = _matrix.so
LIB_ALLOCATOR =  _allocator.cpp _allocator.hpp
ALLOCATOR_TARGET = _allocator.o
LIB_MATRIX = _matrix.cpp _matrix.hpp _allocator.hpp _allocator.cpp
MATRIX_TARGET = _matrix.o
PYB_TARGET = _pybind.o
LIB_PYB = _pybind.cpp
PYBINCLUDE = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LBLS = -lblas


all: clean $(LIB_SHARE_OBJS)


$(LIB_SHARE_OBJS): $(ALLOCATOR_TARGET) $(MATRIX_TARGET)  $(PYB_TARGET)
	$(CXX) $(FLAGS) $^ -o $@ $(LBLS)

$(ALLOCATOR_TARGET): $(LIB_ALLOCATOR)
	$(CXX) $(FLAGS) -c $< -o $@

$(MATRIX_TARGET): $(LIB_MATRIX)
	$(CXX) $(MKLINCLUDE) $(FLAGS) -c $< -o $@

$(PYB_TARGET): $(LIB_PYB)
	$(CXX) $(FLAGS) $(MKLINCLUDE) $(PYBINCLUDE) -c $< -o $@

.PHONY: run test clean

test: $(LIB_SHARE_OBJS)
	python3 -m pytest -v test_matrix.py
	python3 test_matrix.py

clean:
	rm -rf _matrix *.o *.so __pycache__ .pytest_cache