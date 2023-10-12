CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

.PHONY: test clean
_vector.so: _vector.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test: 
	python3 -m pytest -v

clean:
	rm -rf *.o *.so __pycache__ .pytest_cache/  