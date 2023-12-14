TARGET := _matrix$(shell python3-config --extension-suffix)
INCLUDES := $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)  -I/usr/include/mkl
LIBRARYS := -L/usr/lib/x86_64-linux-gnu/mkl -lblas
CXXFLAGS := -O3 -Wall -shared -std=c++11 -fPIC $(LIBRARYS) $(INCLUDES)

$(TARGET): _matrix.cpp
	g++ $^ -o $(TARGET) $(CXXFLAGS) 

.PHONY: clean
clean:
	rm -rf *.so __pycache__ .pytest_cache