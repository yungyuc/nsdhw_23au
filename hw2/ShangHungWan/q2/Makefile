main: main.cpp
	pip install pybind11
	g++ -O3 -Wall -shared -std=c++11 -fPIC $$(python3 -m pybind11 --includes) main.cpp -o main$$(python3-config --extension-suffix)
	mv main$$(python3-config --extension-suffix) ./_vector.so

.PHONY: clean run test
clean:
	rm -rf build/* *.so .pytest_cache
test:
	python3 -m pytest test__vector.py