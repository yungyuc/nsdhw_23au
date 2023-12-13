CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
MKLINCLUDE = /usr/include/mkl
MKLFLAGS = -lblas
PYINCLUDE = /usr/include/python3.11
PYFLAGS = -lpython3.11

main:
	$(CXX) $(CXXFLAGS) -I$(MKLINCLUDE) -I$(PYINCLUDE) `python3 -m pybind11 --includes` _matrix.cpp -o _matrix`python3-config --extension-suffix` $(PYFLAGS) $(MKLFLAGS)

test: main
	python3 -m pytest -v -s

clean:
	rm -rf *.out *.so .pytest_cache* __pycache__*