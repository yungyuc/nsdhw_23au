CC = g++
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC
PYLDFLAGS = $(shell python3-config --ldflags)
PYINCLUDE = $(shell python3 -m pybind11 --includes)
PYESUFFIX = $(shell python3-config --extension-suffix)
TARGET=_vector$(PYESUFFIX)

$(TARGET): vecLib.cpp
	$(CC) $(CFLAGS) $(PYINCLUDE) $(PYLDFLAGS) $< -o $(TARGET)

.PHONY: clean test

test:
	pytest -v
clean:
	rm -rf $(TARGET) .[a-z]* __pycache__


# Some compile format refer to https://pybind11.readthedocs.io/en/stable/basics.html