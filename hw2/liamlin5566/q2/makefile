CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` # for debug
PROG_TARGET = test_angle.py
LIB_TARGET = _vector.so

all: $(LIB_TARGET)
$(LIB_TARGET): utils.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

test: all
	python3 -m pytest -v


clean:
	rm -rf *.o *.so .pytest_cache/ __pycache__/