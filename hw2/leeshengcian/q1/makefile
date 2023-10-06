.PHONY: all run check clean
all: main

run: main
	./main

check: main
	./main > result.txt

main: main.o line.o
	g++ -o main main.o line.o

main.o: main.cpp
	g++ -c main.cpp

line.o: line.cpp line.hpp
	g++ -c line.cpp

clean:
	@rm -rf *.o *.txt main