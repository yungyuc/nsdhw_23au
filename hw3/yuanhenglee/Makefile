CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3 -fPIC 
PYBINDFLAGS = `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LFLAGS = -lblas

BUILD_DIR = bin

SRCS = $(wildcard ./*.cpp)
OBJS = $(patsubst ./%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
LIBS = ./_matrix.so

.PHONY: all clean test benchmark

all: $(LIBS)

$(BUILD_DIR)/%.o: ./%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) -c $< -o $@

$(LIBS): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(OBJS) $(LFLAGS)

$(BUILD_DIR):
	mkdir -p $@

test: $(LIBS)
	python -m pytest -v

clean:
	rm -rf $(BUILD_DIR) $(TEST_DIR)/__pycache__ *.so .pytest_cache

benchmark: $(LIBS)
	python benchmark.py