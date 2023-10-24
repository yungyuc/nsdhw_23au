CXX = g++
CXXFLAGS = -std=c++17 -O3 -g -m64
TARGET = ma03_matrix_matrix
SRCS = ma03_matrix_matrix.cpp

# Include directories for MKL (modify the path as needed)
MKL_INCLUDE = -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include

# Linker flags for MKL (modify the path as needed)
MKL_LIBS = -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin

# Include directories for Pybind11 and Python (modify the path as needed)
PYBIND11_INCLUDE = -I/usr/local/include
PYTHON_INCLUDE = -I/usr/include/python3.10 -I/usr/include/python3.10

# Linker flags for Python
PYTHON_LIBS = $(shell python3-config --ldflags) -lpython3.10

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(MKL_INCLUDE) $(PYBIND11_INCLUDE) $(PYTHON_INCLUDE) -o $(TARGET) $(SRCS) $(MKL_LIBS) $(PYTHON_LIBS) -lmkl_rt

.PHONY: run clean test

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	python3 ./test.py

clean:
	rm -f $(TARGET)

