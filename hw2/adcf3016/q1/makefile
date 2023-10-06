CXX := g++
CPPFLAGS := -g -Wall -std=c++11

TARGET := main
EXE := ./main
OBJS := main.o line.o
DES := result.txt

all: $(TARGET)

$(TARGET): $(OBJS)
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
	rm -rf $(TARGET) $(DES) $(OBJS)


.PHONY : all clean run check
