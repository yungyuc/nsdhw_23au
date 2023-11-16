CC = clang++
CFLAGS = -O3 -Wall -m64 -shared -std=c++11 -fPIC
PYFLAGS = `python3 -m pybind11 --includes` $< -o $@ `python3-config --includes --ldflags`
MKLDIR = -I/usr/include/mkl
MKL_LIB_DIR = /usr/lib/x86_64-linux-gnu
MKL_LIB_SO = libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS = $(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) \
			-lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

SRC = _matrix.cpp
TARGET = $(patsubst %.cpp, %.so, $(SRC))

.PHONY: all clean

all: $(TARGET)

# test: $(TARGET)
# 	python3 -m pytest -v
# 	python3 performance.py

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/

%.so: %.cpp
	$(CC) $(CFLAGS) $(MKLDIR) $(PYFLAGS) ${MKL_LIBS}
