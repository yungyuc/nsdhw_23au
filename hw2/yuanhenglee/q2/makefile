CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O3 -arch x86_64
LDFLAGS = -shared -fPIC
PYBINDFLAGS = $(shell python3 -m pybind11 --includes)

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
LIBS = $(LIB_DIR)/angle_cal$(shell python3-config --extension-suffix)

TEST_DIR = tests

.PHONY: all clean test

all: $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(PYBINDFLAGS) -c $< -o $@

$(LIBS): $(OBJS) | $(LIB_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

test: $(LIBS)
	pytest

clean:
	rm -rf $(BUILD_DIR) $(TEST_DIR)/__pycache__