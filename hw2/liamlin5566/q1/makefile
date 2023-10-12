CXX = g++
CXXFLAGS = -std=c++11 -O3 -g -Wall
FILE = result.txt

all: main.out 

main.out: main.cpp Line.o
	$(CXX) -o $@ $^

Line.o: Line.cpp Line.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:  main.out
	./main.out

check: main.out
	./main.out > $(FILE)

clean:
	rm *.o *.out 
	if [ -f $(FILE) ]; then rm $(FILE); fi
