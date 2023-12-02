CXX = g++
CFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LDFLAGS = -lblas
SRC = mod.cpp
TARGET = _matrix.so

NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")

all: $(TARGET)

$(TARGET): $(SRC)
		$(CXX) $(CFLAGS) $< -I/usr/include/mk -I$(NUMPY) -o $@ ${LDFLAGS}

clean:
	rm -f *.so

.PHONY: all clean test 
