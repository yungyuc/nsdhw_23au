CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3-config --cflags --ldflags` $(PYBIND11_INCLUDE)

PYTHON = python3
PYBIND11_INCLUDE = $(shell $(PYTHON) -m pybind11 --includes)


_vector.so: _vector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test:
	$(PYTHON) -m pytest -q test_VecAngle.py

clean:
	rm -rf _vector.so
	rm -rf __pycache__ .pytest_cache
