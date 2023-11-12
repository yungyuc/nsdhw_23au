CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` # for debug
LFLAGS = -lblas

LIB_TARGET = _matrix.so


all: $(LIB_TARGET)

$(LIB_TARGET): Matrix.cpp Matrix.h
	$(CXX) -o $@ $(CXXFLAGS)  $< $(LFLAGS)

test: all
	python3 -m pytest -v


clean:
	rm -rf $(LIB_TARGET) .pytest_cache/ __pycache__/
