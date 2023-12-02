CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3 -fPIC
PYBINDFLAGS = $(shell python3 -m pybind11 --includes) $(shell python3-config --includes)
MKL = -I/usr/include/mkl
PYSUFFIX = $(shell python3-config --extension-suffix)

SRCS = matrix.cpp
MOD = mod.cpp
TARGET = ./_matrix$(PYSUFFIX)

.PHONY: all clean test benchmark

all: $(TARGET)

$(MOD):
	cp ../$(MOD) .

$(TARGET): $(SRCS) $(MOD)
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) $(MKL) -shared -o $@ $^ -lblas

test: $(TARGET)
	python -m pytest -v

clean:
	rm -rf __pycache__ *.so .pytest_cache