CXX           := g++
CXXFLAGS      := -O3 -Wall -shared -std=c++11 -fPIC
MKLINCLUDE    := /usr/include/mkl
MKLFLAGS      := -lblas
MKL_LIB = -L/usr/lib/x86_64-linux-gnu -lblas -pthread -liomp5 -lm -lmkl_intel_thread -lmkl_intel_lp64 -ldl

INCLUDE = `python3 -m pybind11 --includes`
PYINCLUDE     := $(shell python3-config --includes) 
PYCONFIG      := `python3-config --extension-suffix`


main:
	$(CXX) $(CXXFLAGS) $(INCLUDE) _matrix.cpp -o _matrix$(PYCONFIG) $(PYINCLUDE) $(MKL_LIB) -I$(MKLINCLUDE)


test: main
	python3 -m pytest

clean:
	rm -rf *.o *.so .pytest_cache __pycache__

statistic: clean
	$(CXX) -O3 -Wall -std=c++11 -fPIC statistic.cpp -I$(MKLINCLUDE) -o statistic.out $(MKLFLAGS)
	./statistic.out | tee performance.txt