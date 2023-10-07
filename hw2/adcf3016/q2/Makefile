CXX := g++
CPPFLAGS := -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET := _vector.so
SRC := _vector.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(SRC) -o $(TARGET)

test: $(TARGET)
	python3 -m pytest -v

clean:
	rm -rf *.o *.so __pycache__

.PHONY: all test clean
