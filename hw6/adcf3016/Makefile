CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC
PIBINDFLAG = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LFLAGS = -lblas
TARGET = _matrix.so
SRC = _matrix.cpp

all: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) -o $@ $(CXXFLAGS) $(PIBINDFLAG) $< $(LFLAGS)

test: $(TARGET)
	python3 -m pytest -v -s

clean:
	rm -r -f *.o *.so __pycache__ .pytest_cache

.PHONY: all test clean
