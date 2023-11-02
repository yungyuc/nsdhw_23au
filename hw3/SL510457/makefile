CXX = g++
CXXFLAGS = -std=c++11 -O3 -shared -m64
HEADERS = -I/usr/include/mkl #-I/DATA/lllll/.local/lib/python3.6/site-packages/pybind11/include
PIBINDFLAG = -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
PY_OBJ = _matrix.so
MKL_LIB_DIR=/usr/lib/x86_64-linux-gnu
MKL_LIB_SO=libmkl_def.so libmkl_avx2.so libmkl_core.so libmkl_intel_lp64.so libmkl_sequential.so
MKL_LIBS=$(patsubst %, $(MKL_LIB_DIR)/%, $(MKL_LIB_SO)) \
			-lpthread -lm -ldl -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

all: $(PY_OBJ)

$(PY_OBJ): _matrix.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(HEADERS) $(PIBINDFLAG) ${MKL_LIBS} 

test: $(PY_OBJ)
	python3 -m pytest -v -s

clean:
	rm *.o *.so __pycache__ .pytest_cache performance.txt -r -f