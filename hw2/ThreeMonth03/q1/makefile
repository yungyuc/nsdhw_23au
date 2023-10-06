CXX = g++
FLAGS = -std=c++11 -g -Wall
FILE = result.txt
OBJECTS = Line.o

all: main.out

main.out: main.cpp $(OBJECTS)
	$(CXX) $(FLAGS) $^ -o $@

$(OBJECTS): %.o : %.cpp %.hpp
	$(CXX) $(FLAGS) -c $< -o $@

.PHONY: clean run check

run: main.out
	./main.out

check: main.out
	./main.out > $(FILE)


clean: 
	rm -f *.o *.out
	rm -f $(FILE)