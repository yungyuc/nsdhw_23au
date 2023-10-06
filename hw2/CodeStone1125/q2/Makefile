CC = g++
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

#PYTHON_INCLUDE = $(shell python3 -m pybind11 --includes)
PYTHON_INCLUDE = $(shell python3-config --includes) -Iextern/pybind11/include
# PYTHON_EXTENSION_SUFFIX = $(shell python3-config --extension-suffix)
source_file := _vector.cpp
execute_file = _vector.so

all: $(execute_file)

$(execute_file): $(source_file)

	$(CC) $(CFLAGS) $(PYTHON_INCLUDE) $(source_file) -o $(execute_file)

test:
	python3 -m  pytest -v


clean:
	rm -f $(execute_file) result.txt

.PHONY: all test clean
