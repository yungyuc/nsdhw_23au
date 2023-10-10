CXX = g++
STD = c++17

Line: Line.cpp Line.hpp
	$(CXX) $< -o $@ -std=$(STD)

.PHONY: run check clean

run: Line
	./Line
check:
	./Line > result.txt
clean:
	rm -rf result.txt
	rm -rf Line
	rm Line.cpp
	rm Line.hpp
	rm Makefile
