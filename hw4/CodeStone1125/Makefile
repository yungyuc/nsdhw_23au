CXX = g++  # 使用g++編譯器
CXXFLAGS = -O3 -Wall -shared -std=c++14 -fPIC
TARGET = _matrix
SRC = _matrix.cpp

# 目標：編譯 _matrix.cpp 並生成共享庫
$(TARGET).so: $(SRC)
	$(CXX) $(CXXFLAGS) -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include -I/usr/include/python3.10 -I/opt/intel/mkl/include $< -o $@ -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

test: $(SRC)
	$(CXX) $(CXXFLAGS) -I/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/include -I/usr/include/python3.10  -I/opt/intel/mkl/include $< -o $(TARGET).so -L/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin -lmkl_rt -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
	python3 -m pytest

# 清理生成的文件
clean:
	rm -rf *.so matrixMat*.bin
	find .. -type d -name "__pycache__" -exec rm -r {} +
	find .. -type d -name ".pytest_cache" -exec rm -r {} +