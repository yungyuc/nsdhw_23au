# CXX = g++
# CXXFLAGS = -O3 -Wall -shared -std=c++14 -fPIC
# TARGET = _matrix
# SRC = _matrix.cpp
# MKL_INC = -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include
# MKL_LIB = -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

# $(TARGET).so: $(TARGET).o
# 	$(CXX) $(CXXFLAGS) $< -o $@ $(MKL_LIB)

# $(TARGET).o: $(SRC)
# 	$(CXX) $(CXXFLAGS) $(MKL_INC) -I/usr/include/python3.10 -I/opt/intel/mkl/include -c $< -o $@

# test: $(TARGET).so
# 	python3 -m pytest

# clean:
# 	rm -rf *.so *.o matrixMat*.bin
# 	find .. -type d -name "__pycache__" -exec rm -r {} +
# 	find .. -type d -name ".pytest_cache" -exec rm -r {} +

# CXX = g++
# CXXFLAGS = -O3 -Wall -shared -std=c++14 -fPIC
# TARGET = _matrix
# SRC = _matrix.cpp

# # Use pkg-config to get MKL include and library flags
# MKL_INC = $(shell pkg-config --cflags mkl)
# MKL_LIB = $(shell pkg-config --libs mkl)

# $(TARGET).so: $(SRC)
# 	$(CXX) $(CXXFLAGS) $(MKL_INC) -I/usr/include/python3.10 -c $< -o $(TARGET).o
# 	$(CXX) $(CXXFLAGS) $(TARGET).o -o $@ $(MKL_LIB)

# test: $(SRC)
# 	$(CXX) $(CXXFLAGS) $(MKL_INC) -I/usr/include/python3.10 -c $< -o $(TARGET).so
# # python3 -m pytest
# 	../validate.py

# .PHONY: clean test

# clean:
# 	rm -rf *.so matrixMat*.bin *.o
# 	find .. -type d -name "__pycache__" -exec rm -r {} +
# 	find .. -type d -name ".pytest_cache" -exec rm -r {} +

CXX = g++
EXE = _matrix$(shell python3-config --extension-suffix)

FLAGS = -O3 -Wall -shared -fPIC -std=c++17
PYBD11 = -I /usr/include/python3.10 -I /usr/include/pybind11 -lpython3.10 `python3 -m pybind11 --includes`
BLAS = -I /usr/include/mkl/ -L /usr/lib/x86_64-linux-gnu -lblas

.PHONY: clean

all: $(SRC)
	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) _matrix.cpp $(PYBD11) $(BLAS) -o $(EXE)	

test: $(SRC)
	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) _matrix.cpp $(PYBD11) $(BLAS) -o $(EXE)	
# python3 -m pytest test.py
	../validate.py

clean:
	rm -rf *.so .pytest_cache __pycache_