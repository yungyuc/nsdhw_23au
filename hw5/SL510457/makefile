CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
MKLINCLUDE = /usr/include/mkl
MKLFLAGS = -lblas
PYINCLUDE = /usr/include/python3.8
NUMPYINCLUDE = `python3 -c 'import numpy; print(numpy.get_include())'`
PYFLAGS = -lpython3.8

main:
	$(CXX) $(CXXFLAGS) -I$(MKLINCLUDE) -I$(PYINCLUDE) -I$(NUMPYINCLUDE) -I./ `python3 -m pybind11 --includes` ../mod.cpp -o _matrix`python3-config --extension-suffix` $(PYFLAGS) $(MKLFLAGS)

test: main
	python3 -m pytest -v -s

clean:
	rm -rf *.out *.so .pytest_cache* __pycache__*