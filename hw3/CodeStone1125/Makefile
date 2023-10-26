# CXX = g++  # 使用g++編譯器
# CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC
# TARGET = _matrix
# SRC = _matrix.cpp
# # 使用python3-config和pybind11工具查找所需的編譯參數
# PYTHON_INCLUDES = -I/usr/include/python3.10 #$(shell python3-config --cflags)
# PYTHON_EXTENSION_SUFFIX = #$(shell python3-config --extension-suffix)

# # Include directories for MKL (modify the path as needed)
# MKL_INCLUDE = -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include
# # Linker flags for MKL (modify the path as needed)
# MKL_LIB_DIR = -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin
# MKL_LIBS = -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

# # Define CBLAS_INDEX explicitly
# CXXFLAGS += -DCBLAS_INDEX=size_t

# # 目標：編譯 _matrix.cpp 並生成共享庫
# $(TARGET)$(PYTHON_EXTENSION_SUFFIX): $(SRC)
# 	$(CXX) $(CXXFLAGS) $(MKL_INCLUDE) $(PYTHON_INCLUDES) $< -o $@ $(MKL_LIB_DIR) $(MKL_LIBS)

# # $(CXX) $(CXXFLAGS) $(MKL_INCLUDE) $(PYTHON_INCLUDES) $(SRC) -o $(TARGET)$(PYTHON_EXTENSION_SUFFIX) $(MKL_LIB_DIR) $(MKL_LIBS)
# test: $(SRC)
	
# 	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC -DCBLAS_INDEX=size_t -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include _matrix.cpp -o _matrix.cpython-310-x86_64-linux-gnu.so -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
# 	python3 -m pytest

# try: $(SRC)
# 	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC -DCBLAS_INDEX=size_t -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include _matrix.cpp -o _matrix.cpython-310-x86_64-linux-gnu.so -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core


# # 清理生成的文件
# clean:
# 	rm -rf $(TARGET)$(PYTHON_EXTENSION_SUFFIX) *.o matrixMat*.bin
# 	find .. -type d -name "__pycache__" -exec rm -r {} +
# 	find .. -type d -name ".pytest_cache" -exec rm -r {} +

CXX = g++  # 使用g++編譯器
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC
TARGET = _matrix
SRC = _matrix.cpp

# 目標：編譯 _matrix.cpp 並生成共享庫
$(TARGET).so: $(SRC)
	$(CXX) $(CXXFLAGS) -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include -I/usr/include/python3.10 $< -o $@ -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

test: $(SRC)
	$(CXX) $(CXXFLAGS) -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include -I/usr/include/python3.10 $< -o $@ -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
	python3 -m pytest

# 清理生成的文件
clean:
	rm -rf $(TARGET)$(PYTHON_EXTENSION_SUFFIX) *.o matrixMat*.bin
	find .. -type d -name "__pycache__" -exec rm -r {} +
	find .. -type d -name ".pytest_cache" -exec rm -r {} +