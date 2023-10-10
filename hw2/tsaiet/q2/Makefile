CXX = g++
FLAG = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET = _vector.so

$(TARGET): _vector.cpp
	$(CXX) $(FLAG) _vector.cpp -o $(TARGET) $(FLAG)

.PHONY: test clean

test: _vector.so
	python3 -m pytest

clean: 
	rm -rf *.so .pytest_cache __pycache__
