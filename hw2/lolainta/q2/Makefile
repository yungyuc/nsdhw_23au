CXX := g++
CXXFLAGS := -std=gnu++17 -O3 -Wall -fPIC
LDFLAGS := -shared
INCLUDES := -Iextern/pybind11/include $(shell python3-config --includes)
TARGET := _vector$(shell python3-config --extension-suffix)

.PHONY: all clean

all: $(TARGET)

$(TARGET): moon.o
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o $(TARGET)