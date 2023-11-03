MKL_INCLUDE_DIR = /usr/include/mkl
MKL_LIB_FLAGS   = -lmkl_rt

PYTHON_EXEC     = python3
PYTHON_INC      = $(shell $(PYTHON_EXEC)-config --includes)
PYBIND11_INC    = $(shell $(PYTHON_EXEC) -m pybind11 --includes)
PYTHON_EXT_SUFFIX = $(shell $(PYTHON_EXEC)-config --extension-suffix)

MODULE_NAME     = _matrix
PYTHON_MODULE_TARGET = $(MODULE_NAME)$(PYTHON_EXT_SUFFIX)

CXX             = g++
CXXFLAGS        = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES        = -I$(MKL_INCLUDE_DIR) $(PYTHON_INC) $(PYBIND11_INC)
LDFLAGS         = $(MKL_LIB_FLAGS)

SRC          = _matrix.cpp

.PHONY: all test clean

all: $(PYTHON_MODULE_TARGET)

$(PYTHON_MODULE_TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

test: $(PYTHON_MODULE_TARGET)
	$(PYTHON_EXEC) test_matrix.py
	$(PYTHON_EXEC) -m pytest -v test_matrix.py

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/