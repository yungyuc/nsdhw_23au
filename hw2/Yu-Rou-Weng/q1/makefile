CXX = g++
SRC = line.cpp

TARGET = line

all: $(TARGET)

$(TARGET): line.o
	$(CXX) -std=c++11 -Wall -Wextra $^ -o $@

line.o: line.cpp
	$(CXX) -std=c++11 -Wall -Wextra -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) result.txt *.o
.PHONY: clean

run: $(TARGET)
	./$(TARGET)
.PHONY: run

check: 
	./$(TARGET) > result.txt
.PHONY: check