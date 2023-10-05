CC = g++
CFLAGS = -std=c++11 -O3 -Wall -shared -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`

source_file := _vector.cpp
execute_file = _vector

all: $(execute_file)

$(execute_file): $(source_file)
	
	$(CC) $(CFLAGS) $(source_file) -o $(execute_file)

test:
	python3 ./test.py


clean:
	rm -f $(execute_file) result.txt

.PHONY: all test clean
