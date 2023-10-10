CXX = g++

_vector: _vector.cpp
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` $< -o $@`python3-config --extension-suffix`

.PHONY: test clean

test: _vector
	python3 -m pytest

clean: 
	rm -rf *.so .pytest_cache __pycache__
