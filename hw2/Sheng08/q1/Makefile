CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXE = main

.PHONY: all run check clean

all: $(EXE)

$(EXE): main.o Line.o
	$(CXX) $(CXXFLAGS) -o $(EXE) main.o Line.o

main.o: main.cpp Line.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Line.o: Line.cpp Line.hpp
	$(CXX) $(CXXFLAGS) -c Line.cpp

run: $(EXE)
	./$(EXE)

check: $(EXE)
	./$(EXE) > result.txt

clean:
	rm -f $(EXE) *.o result.txt
