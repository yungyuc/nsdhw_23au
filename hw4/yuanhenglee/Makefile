CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -fPIC 
PYBINDFLAGS = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LFLAGS = -lblas

BUILD_DIR = bin
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/allocator.o
TARGET = ./_matrix.so

.PHONY: all clean test benchmark

all: $(TARGET)

$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) $^ -shared -o $@ $(LFLAGS)


$(BUILD_DIR):
	mkdir -p $@

test: $(TARGET)
	python -m pytest -v

clean:
	rm -rf $(BUILD_DIR) __pycache__ *.so .pytest_cache

benchmark: $(TARGET)
	python benchmark.py