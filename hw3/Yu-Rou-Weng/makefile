CXX = g++
SRC = _matrix.cpp
EXE = _matrix$(shell python3-config --extension-suffix)
FLAGS = -O3 -Wall -shared -fPIC
PYBD11 = -I /usr/include/python3 -I /usr/include/pybind11 `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

BLAS = -I /usr/include/mkl/ -L /usr/lib/x86_64-linux-gnu/mkl/ -lblas

.PHONY: all clean

all: $(TARGET)
	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) $(PYBD11) $(BLAS) $(SRC) -o $(EXE)

run: $(TARGET)
	$(CXX) $(FLAGS) $(shell python3 -m pybind11 --includes) $(PYBD11) $(BLAS) $(SRC) -o $(EXE)

test: $(TARGET)
	$(CXX) $(FLAGS) $(PYBD11) $(SRC) -o $(EXE) $(BLAS)
	python3 -m pytest -v -s

clean:
	rm -rf *.o *.out *.so __pycache__/ .pytest_cache/