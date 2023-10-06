CXX := g++
CPPFLAGS := -g -Wall -std=c++11

TARGET := main
EXE := ./main
OBJ := main.o line.o
SRC := main.cpp line.cpp line.hpp
DES := result.txt

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(CPPFLAGS)

main.o: main.cpp line.hpp
	$(CXX) -c $< -o $@ $(CPPFLAGS)

line.o: line.cpp line.hpp
	$(CXX) -c $< -o $@ $(CPPFLAGS)

run:
	$(EXE)

check:
	$(EXE) > $(DES)

clean:
	rm -rf $(TARGET) $(DES)


.PHONY : all clean run check
