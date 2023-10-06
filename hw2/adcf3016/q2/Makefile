CXX := g++
CPPFLAGS := -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET := calculate_radian.so
SRC := calculate_radian.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(SRC) -o $(TARGET)

test: $(TARGET)
	python3 -m pytest

clean:
	rm -rf *.o *.so __pycache__

.PHONY: all test clean
