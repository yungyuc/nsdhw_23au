.PHONY: all test clean

all: angle_calculation.so

angle_calculation.so: angle.cpp
	g++ -Wall -03 angle.cpp -o angle_calculation.so -shared -std=c++17 -fPIC -I/usr/include/python3.11 -I/usr/include/pybind11 -lpython3.11 `python3 -m pybind11 --includes`

test: all
	python3 -m pytest -v

clean:
	@rm -rf *.o *.so .pytest_cache/ __pycache__/