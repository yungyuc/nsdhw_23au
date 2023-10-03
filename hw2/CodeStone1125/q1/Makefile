CC := g++
CFLAGS := -std=c++11 -Wall
source_file := line.cpp line.hpp #1 is number
execute_file = out

all: $(execute_file)

$(execute_file): $(source_file)
	$(CC) $(CFLAGS) $(source_file) -o $(execute_file)

run: $(source_file)
	./$(execute_file)

check: $(source_file)
	./$(execute_file) > result.txt

clean:
	rm -f $(execute_file) result.txt

.PHONY: all run check clean
