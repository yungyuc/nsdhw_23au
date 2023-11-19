main: main.cpp
	pip install pybind11
	sudo apt install liblapack-dev liblapack3 libopenblas-base libopenblas-dev
	g++ -O3 -Wall -shared -std=c++11 main.cpp ByteCounter.cpp -o _matrix.so -I includes/ -I /opt/OpenBLAS/include/ -L/opt/OpenBLAS/lib -lopenblas $$(python3 -m pybind11 --includes) -fPIC

.PHONY: clean test
clean:
	rm -f *.so
test:
	make && python3 -m pytest