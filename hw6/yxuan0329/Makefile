CXX = g++
CFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LDFLAGS = -lblas
MKL_PATH = /usr/lib/x86_64-linux-gnu/libmkl_rt.so
SRC = mod.cpp
TARGET = _matrix.so

NUMPY = $(shell python3 -c "import numpy; print(numpy.get_include())")

all: $(TARGET)

$(TARGET): $(SRC)
		$(CXX) $(CFLAGS) $< -I/usr/include/mk -I$(NUMPY) -o $@ ${LDFLAGS} ${MKL_PATH}

clean:
	rm -f *.so