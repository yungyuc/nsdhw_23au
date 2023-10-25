CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET = _vector.so
TEST_FILE = test

.PHONY: all test clean

all: $(TARGET)
$(TARGET): _vector.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

test: all
	python3 -m pytest -v

clean:
	rm -rf *.o *.so __pycache__ .pytest_cache/
