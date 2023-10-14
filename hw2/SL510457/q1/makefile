CC = g++
CFLAGS = -std=c++11 -Wall
DEPS = line.hpp
OBJ = main.o line.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: main
	./main
	
check:
	@echo "No tests to run"


.PHONY: clean run

clean:
	rm -f *.o main