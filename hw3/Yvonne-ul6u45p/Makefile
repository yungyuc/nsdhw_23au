CXX = g++	# compiler
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
MKLROOT = /opt/intel/oneapi/mkl/2023.2.0
MKL_INCLUDE = /opt/intel/oneapi/mkl/2023.2.0/include
MKL_LIB = /opt/intel/oneapi/mkl/2023.2.0/lib/intel64
TARGET = _matrix.so
MAIN = matrixMultiply

all: $(TARGET)

$(TARGET): $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(MAIN).cpp -o $(TARGET) -L$(MKL_LIB) -I$(MKL_INCLUDE) -lblas

# $(MAIN): $(MAIN).cpp
# 	g++ -std=c++17 -O3 -Wall matrixMultiply.cpp -o matrixMultiply -L/opt/intel/oneapi/mkl/2023.2.0/lib/intel64 -I/opt/intel/oneapi/mkl/2023.2.0/include -lblas

.PHONY: test
test:
	python3 -m pytest -v
	python3 benchmark.py
# make test should run the same unit tests.

.PHONY: clean
clean:
	rm -rf $(MAIN) *.o *.so *.txt .pytest_cache __pycache__
# make clean needs to remove all the built and intermediate files.
