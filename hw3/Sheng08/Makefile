CXX           := g++
CXXFLAGS      := -O3 -Wall -shared -std=c++11 -fPIC
MKLINCLUDE    := /usr/include/mkl
MKLFLAGS      := -lblas
PYTHON 		  := python3
PYINCLUDE     := $(shell python3-config --includes) 
PYBINDINCLUDE := $(shell python3 -m pybind11 --includes)
PYCONFIG      := $(shell python3-config --extension-suffix)
SRC        	  := _matrix.cpp
TARGET 		  := _matrix${PYCONFIG}

.PHONY: all main test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -I$(MKLINCLUDE) ${PYINCLUDE} ${PYBINDINCLUDE} $^ -o $@ $(MKLFLAGS) 

test: $(TARGET)
	$(PYTHON) test_matrix.py
	$(PYTHON) -m pytest -v test_matrix.py
	
clean:
	rm -f $(TARGET) $(OBJ)
	find . -name "__pycache__" -type d -exec rm -rf {} +
	find . -name "*.pyc" -type f -delete
	find . -name ".pytest_cache" -type d -exec rm -rf {} +