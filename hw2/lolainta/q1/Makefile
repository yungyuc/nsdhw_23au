CXX := g++
CXXFLAGS := -std=gnu++17 -Wall -Wextra -Werror -pedantic -O3

.PHONY: all run check clean

all: q1

run: q1
	./q1

check: q1
	./q1 > result.txt

clean:
	rm -f q1 *.o *.txt

q1: main.o line.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

