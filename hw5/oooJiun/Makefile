CC= clang++
CFLAGS = -O3 -Wall -m64 -shared -std=c++17 -fPIC
PYFLAGS = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
MKLDIR = -I/usr/include/mkl
MKL_LIB_DIR = /usr/lib/x86_64-linux-gnu
MKL_LIB_SO = libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS = $(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) \
			-lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5
TARGET = _matrix`python3 -config --extension-suffix`

SRC = ../mod.cpp

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(MKLDIR) $(PYFLAGS) $< -o $@.so ${MKL_LIBS}

.PHONY: clean

clean: 
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/