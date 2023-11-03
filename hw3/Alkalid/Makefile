

all: _matrix.cpp
	g++ $< -o $@ -std=c++11 -O3 -shared -m64 -I/usr/include/mkl -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` -lblas

test: all
	python3 -m pytest -v -s

clean:
	rm *.o *.so __pycache__ .pytest_cache performance.txt -r -f