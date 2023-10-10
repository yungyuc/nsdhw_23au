main: main.cpp
	g++ -o main main.cpp

.PHONY: clean run check
clean:
	rm -f main result.txt
run:
	./main
check:
	./main > result.txt