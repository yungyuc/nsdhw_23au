CXX = g++
Line: Line.o
	$(CXX) $^ -o $@

Line.o: Line.cpp Line.hpp
	$(CXX) -c $< -o $@

.PHONY: clean run check
run: Line
	./Line

check: Line
	./Line > result.txt

clean:
	rm -f *.o *.txt Line