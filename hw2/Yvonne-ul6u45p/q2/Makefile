CXX = g++	# compiler
CXXFLAGS = -std=c++17 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
TARGET = _vector.so

all: $(TARGET)

$(TARGET): calculateAngle.cpp
	$(CXX) $(CXXFLAGS) calculateAngle.cpp -o $(TARGET)
# When a source file changes, make needs to pick it up and rebuild.

.PHONY: test
test:
	python3 -m pytest -v
# make test runs the Python-based tests.

.PHONY: clean
clean:
	rm -rf *.o *.so .pytest_cache __pycache__
# make clean needs to remove all the built and intermediate files.
