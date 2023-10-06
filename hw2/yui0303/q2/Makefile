CC = g++
CFLAGS = -Wall -shared -std=c++11 -fPIC
PYINCLUDE = $(shell python3 -m pybind11 --includes)
PYESUFFIX = $(shell python3-config --extension-suffix)
TARGET=_vector$(PYESUFFIX)

$(TARGET): vecLib.cpp
	$(CC) $(CFLAGS) $(PYINCLUDE) $< -o $(TARGET)

.PHONY: clean test

test:
	pytest -v
clean:
	rm -rf $(TARGET) .[a-z]* __pycache__


# Some compile format refer to https://pybind11.readthedocs.io/en/stable/basics.html