CC= clang++
CFLAGS = -O3 -Wall -m64 -shared -std=c++17 -fPIC -I./
PYFLAGS = -I /usr/include/python3 -I /usr/include/pybind11 `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
NPFLAGS = -I`python3 -c 'import numpy;print(numpy.get_include())'`
MKLDIR = -I /usr/include/mkl
MKLFLAGS = $(MKLDIR) -L /usr/lib/ -I/usr/include/openblas/openblas/ -lblas
MKL_LIB_DIR = /usr/lib/x86_64-linux-gnu
MKL_LIB_SO = libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS = $(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) \
			-lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

TARGET = _matrix
SRC = _matrix.cpp

.PHONY: all clean

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(NPFLAGS) $(MKLFLAGS) $(PYFLAGS) -o $(TARGET) ${MKL_LIBS}

clean: 
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/