CXX = g++
CXXFLAGS = -O3 -Wall --shared -std=c++17 -fPIC `python3 -m pybind11 --includes` `python3-config --includes`
CXXLDFLAGS = `python3-config --ldflags`
TARGET = angle
TEST_FILE = test

.PHONY: all test clean

all: %.so $(TEST_FILE).py

%.so: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)`python3-config --extension-suffix`

test: %.so $(TEST_FILE).py
	python3 -m pytest -v

clean:
	rm -rf *.so __pycache__ .pytest*