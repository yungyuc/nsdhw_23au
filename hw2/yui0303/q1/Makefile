CC=g++
EXE=main

$(EXE): main.o line.o
	$(CC) $^ -o $@

main.o: main.cpp line.hpp
	$(CC) -c $< -o $@

line.o: line.cpp line.hpp
	$(CC) -c $< -o $@

.PHONY: run check clean

run: 
	./$(EXE)

check:
	./$(EXE) > result.txt

clean: 
	rm -f *.o result.txt $(EXE)

# $@ target file name
# $< fist dependency in the list of dependencies
# $^ all dependencies
# $* represents the stem of the target filename.