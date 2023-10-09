CXX = g++
FLAGS = -O3 -Wall -shared -std=c++11 -fPIC
INCLUDES = $(shell python3-config --includes) $(shell python3 -m pybind11 --includes)
PY3SUFFIX = $(shell python3-config --extension-suffix)
TARGET = _vector$(PY3SUFFIX)

$(TARGET): cal_angle.cpp
	$(CXX) $(FLAGS) $(INCLUDES) -o $@ $<

test:
	python3 -m pytest -v
.PHONY: test

clean:
	rm -rf __pycache__/ .pytest_cache/
	rm -f *.o *.so
.PHONY: clean