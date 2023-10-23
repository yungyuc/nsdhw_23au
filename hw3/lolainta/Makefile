CXX := g++
CXXFLAGS := -std=gnu++17 -O3 -Wall -fPIC
LDFLAGS := -shared
INCLUDES := -Iextern/pybind11/include $(shell python3-config --includes) -Iinclude -I/opt/intel/mkl
TARGET := _matrix$(shell python3-config --extension-suffix)

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET) 
	python3 -m pytest -v 