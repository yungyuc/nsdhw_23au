CXX = g++
CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

PYTHON = python3
PYBIND11_INCLUDES = $(shell $(PYTHON) -m pybind11 --includes)
PYTHON_CONFIG = $(shell which $(PYTHON)-config)
PY_EXTENSION_SUFFIX = $(shell $(PYTHON_CONFIG) --extension-suffix)

SRC = _vector.cpp
TARGET = _vector$(PY_EXTENSION_SUFFIX)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(PYBIND11_INCLUDES) $^ -o $@

clean:
	rm -f $(TARGET)

test:
	$(PYTHON) -m pytest test_VecAngle.py