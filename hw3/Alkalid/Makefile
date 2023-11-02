LFLAGS = -lblas

LIB_TARGET = _matrix.so

all:
	g++ -o $(LIB_TARGET) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` _matrix.cpp $(LFLAGS)

test: all
	python3 -m pytest -v

clean:
	rm -rf $(LIB_TARGET) .pytest_cache/ __pycache__/