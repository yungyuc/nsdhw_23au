CXX=clang++
CXXFLAGS=-std=c++17 -O3  -m64 -shared -fPIC -I ./ -I /usr/include/mkl


PYBIND=$(shell python3 -m pybind11 --includes)
PYCONFIG=$(shell python3-config --extension-suffix)
NP_INC=$(shell python3 -c "import numpy; print(numpy.get_include())")

MKL_LIB_DIR=/usr/lib/x86_64-linux-gnu
MKL_LIBS=${MKL_LIB_DIR}/libmkl_def.so \
		${MKL_LIB_DIR}/libmkl_avx2.so \
		${MKL_LIB_DIR}/libmkl_core.so \
		${MKL_LIB_DIR}/libmkl_intel_lp64.so \
		${MKL_LIB_DIR}/libmkl_sequential.so

all:
	${CXX} $(CXXFLAGS)  $(PYBIND) ../mod.cpp -o _matrix$(PYCONFIG) -I$(NP_INC) -I /usr/include/python3.8 $(MKL_LIBS)

clean:
	rm -rf *.so __pycache__ ../.pytest_cache .pytest_cache ../.vscode performance.txt