.PHONY: all test clean

all: angle_calculation.so

angle_calculation.so: angle.o
	g++ -o angle.o

angle.o: angle.cpp
	g++ -c angle.cpp

test: all
	python3 -m pytest -v

clean:
	@rm -rf *.o *.so .pytest_cache/ __pycache__/