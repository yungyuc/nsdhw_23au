CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC $(shell python3 -m pybind11 --includes) $(shell python3-config --includes --ldflags)

PYTHON = python3

SRC = _vector.cpp
PYESUFFIX = $(shell python3-config --extension-suffix)
TARGET = _vector$(PYESUFFIX)

.PHONY: all test clean

all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test rule
test: $(TARGET)
	$(PYTHON) -m pytest -v test_vector_angle.py

# Cleanup rule
clean:
	rm -f $(TARGET)
	find . -name "__pycache__" -type d -exec rm -rf {} +
	find . -name "*.pyc" -type f -delete
	find . -name ".pytest_cache" -type d -exec rm -rf {} +