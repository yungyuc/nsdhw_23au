CXX = g++
FLAG = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET = _matrix.so

$(TARGET): _matrix.cpp
	$(CXX) $(FLAG) _matrix.cpp -o $(TARGET) $(FLAG)

.PHONY: test clean

test: _matrix.so performance.py
	python3 performance.py -m pytest

clean: 
	rm -rf *.so .pytest_cache __pycache__ *.txt