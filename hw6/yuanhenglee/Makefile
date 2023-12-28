CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -fPIC
PYBINDFLAGS = $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
MKL = -I/usr/include/mkl
PYSUFFIX = $(shell python3-config --extension-suffix)

SRCS = matrix.cpp main.cpp
TARGET = ./_matrix$(PYSUFFIX)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRCS) 
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) $(MKL) -shared -o $@ $^ -lblas

test: $(TARGET)
	python -m pytest -v

clean:
	rm -rf __pycache__ .pytest_cache $(TARGET)