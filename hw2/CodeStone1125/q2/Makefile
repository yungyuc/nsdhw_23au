CC = g++
CFLAGS = -O3 -Wall -shared -std=c++11 -fPIC

PYTHON_INCLUDE = $(shell python3 -m pybind11 --includes)
PYTHON_EXTENSION_SUFFIX = $(shell python3-config --extension-suffix)

source_file := vectors_module.cpp
execute_file = vectors_module$(PYTHON_EXTENSION_SUFFIX)

all: $(execute_file)

$(execute_file): $(source_file)
	
	$(CC) $(CFLAGS) $(PYTHON_INCLUDE) $(source_file) -o $(execute_file)

test:
	python3 ./test.py


clean:
	rm -f $(execute_file) result.txt

.PHONY: all test clean
