CXX = g++
PYBIND11_INCLUDE = $(shell python3 -m pybind11 --includes)
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3-config --cflags --ldflags` $(PYBIND11_INCLUDE)

_vector.so: angle.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test:
	python3 -m pytest -q test_vector.py

clean:
	rm -rf _vector.so
	rm -rf __pycache__ .pytest_cache
