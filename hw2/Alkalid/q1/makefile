.PHONY: clean
.PHONY: check
.PHONY: run

main: main.o line.o
	g++ main.o line.o -o main -Wall

main.o: main.cpp
	g++ -c main.cpp -o main.o -Wall
line.o: line.cpp line.h
	g++ -c line.cpp -o line.o -Wall
run: main
	./main
check: main
	./main > result.txt
clean:
	rm -rf *.o main *.txt