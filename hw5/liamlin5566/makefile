

CXX := g++
CXXFLAGS := -O3 -std=c++17 -fPIC -Wall -Wextra -pedantic 
LFLAGS := -lblas

PYTHON_INCLUDES := `python3 -m pybind11 --includes` `python3-config --includes`

LIB := _matrix.so #main.out #

SRCS := $(wildcard ./*.cpp)
OBJS := $(patsubst ./%.cpp, ./%.o,$(SRCS)) #Matrix.o CustomAllocator.o  #



all: $(LIB)

$(LIB): matrix.o mod.o
	$(CXX) $(CXXFLAGS) -shared -o $@ $(OBJS) $(LFLAGS)

%.o: %.cpp matrix.h
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDES) -o $@ -c $<

test: all
	python3 -m pytest -v

clean:
	rm -rf $(LIB) *.o *.so .pytest_cache/ __pycache__/
