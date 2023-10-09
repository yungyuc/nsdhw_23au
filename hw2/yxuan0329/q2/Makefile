CXX = g++
CFLAGS = -std=c++11 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET = _vector.so

all: $(TARGET)

$(TARGET): getAngle.cpp
	$(CXX) $(CFLAGS) getAngle.cpp -o $(TARGET) $(LFLAGS)

.PHONY: test
test:
	python3 -m pytest getAngleTest.py -v

.PHONY: clean
clean:
	rm -rf $(TARGET)

