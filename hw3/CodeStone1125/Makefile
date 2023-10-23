CXX = g++
CXXFLAGS = -std=c++17 -O3 -g -m64
TARGET = ma03_matrix_matrix
SRCS = ma03_matrix_matrix.cpp

# Include directories for MKL (modify the path as needed)
MKL_INCLUDE = -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include

# Linker flags for MKL (modify the path as needed)
MKL_LIBS = -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(MKL_INCLUDE) -o $(TARGET) $(SRCS) $(MKL_LIBS) -lmkl_rt

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)



