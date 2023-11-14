# CXX = g++
# EXE = _matrix$(shell python3-config --extension-suffix)

# FLAGS = -O3 -Wall -shared -fPIC -std=c++17
# PYBD11 = -I /usr/include/python3.10 -I /usr/include/pybind11 -lpython3.10 `python3 -m pybind11 --includes`
# BLAS = -I /usr/include/mkl/ -L /usr/lib/x86_64-linux-gnu -lblas

# .PHONY: clean

# all: $(SRC)
# 	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) _matrix.cpp $(PYBD11) $(BLAS) -o $(EXE)	

# test: $(SRC)
# 	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) _matrix.cpp $(PYBD11) $(BLAS) -o $(EXE)	
# 	../validate.py

# clean:
# 	rm -rf *.so .pytest_cache __pycache_

CXX = g++
EXE = _matrix$(shell python3-config --extension-suffix)
SRC = _matrix.cpp

FLAGS = -O3 -Wall -shared -fPIC -std=c++17
PYBIND11_INCLUDES = $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDES = -I /usr/include/python3.10
PYBIND11_LIB = -lpython3.10

MKL_INCLUDE = -I /usr/include/mkl/
MKL_LIB = -L /usr/lib/x86_64-linux-gnu -lblas

.PHONY: all test clean

all: $(EXE)

test: $(EXE)
	$(CXX) $(FLAGS) $(PYBIND11_INCLUDES) $(PYTHON_INCLUDES) $(MKL_INCLUDE) $< $(PYBIND11_LIB) $(MKL_LIB) -o $@
	../validate.py

$(EXE): $(SRC)
	$(CXX) $(FLAGS) $(PYBIND11_INCLUDES) $(PYTHON_INCLUDES) $(MKL_INCLUDE) $< $(PYBIND11_LIB) $(MKL_LIB) -o $@

clean:
	rm -rf *.o *.so .pytest_cache __pycache_ test

