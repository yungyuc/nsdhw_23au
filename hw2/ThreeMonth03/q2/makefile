CXX = g++
FLAGS = -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LIB_TARGET = _vector.so

all: $(LIB_TARGET)
$(LIB_TARGET): customized_calculation.cpp
	$(CXX) $(FLAGS) $< -o $@

.PHONY: test clean

test: all
	python3 -m pytest -v

clean:
	rm -rf .pytest_cache/ __pycache__/
	rm -f *.o *.so