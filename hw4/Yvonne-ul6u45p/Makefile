CXX = g++	# compiler
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
# MKLROOT = /opt/intel/oneapi/mkl/2023.2.0
# MKL_INCLUDE = $(MKLROOT)/include
# MKL_LIB = $(MKLROOT)/lib/intel64
MKL_INCLUDE = /usr/include/mkl
MKL_LIB = /usr/lib/x86_64-linux-gnu/mkl
MAIN = _matrix

# all: $(MAIN).so

$(MAIN).so: $(MAIN).cpp
	$(CXX) $(CXXFLAGS) $(MAIN).cpp -o $(MAIN).so -L$(MKL_LIB) -I$(MKL_INCLUDE) -lblas

# $(MAIN): $(MAIN).cpp
# 	g++ -std=c++17 -O3 -Wall _matrix.cpp -o _matrix -L/opt/intel/oneapi/mkl/2023.2.0/lib/intel64 -I/opt/intel/oneapi/mkl/2023.2.0/include -lblas

.PHONY: test
test:
	python3 -m pytest -v

.PHONY: clean
clean:
	rm -rf $(MAIN) *.so .pytest_cache __pycache__
# make clean needs to remove all the built and intermediate files.
