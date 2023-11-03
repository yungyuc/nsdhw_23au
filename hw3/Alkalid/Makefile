# Makefile to build Python extension using MKL and Pybind11

# Directories and flags for MKL
MKL_INCLUDE_DIR = /usr/include/mkl
MKL_LIB_FLAGS   = -lmkl_rt

# Python configuration
PYTHON_EXEC     = python3
PYTHON_INC      = $(shell $(PYTHON_EXEC)-config --includes)
PYBIND11_INC    = $(shell $(PYTHON_EXEC) -m pybind11 --includes)
PYTHON_EXT_SUFFIX = $(shell $(PYTHON_EXEC)-config --extension-suffix)

# Target module name
MODULE_NAME     = _matrix
PYTHON_MODULE_TARGET = $(MODULE_NAME)$(PYTHON_EXT_SUFFIX)

# Compiler and linker flags
CXX             = g++
CXXFLAGS        = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES        = -I$(MKL_INCLUDE_DIR) $(PYTHON_INC) $(PYBIND11_INC)
LDFLAGS         = $(MKL_LIB_FLAGS)

# Source files
SOURCE          = _matrix.cpp

.PHONY: all test clean

# Default target
all: $(PYTHON_MODULE_TARGET)

$(PYTHON_MODULE_TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

# Test target
test: $(PYTHON_MODULE_TARGET)
	$(PYTHON_EXEC) test_matrix.py
	$(PYTHON_EXEC) -m pytest -v test_matrix.py

# Clean target
clean:
	rm -rf *.o *.so .pytest_cache __pycache__