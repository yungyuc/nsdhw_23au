CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O3 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LDFLAGS = -shared -fPIC

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
LIBS = ./_vector$(shell python3-config --extension-suffix)

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
	python -m pytest -v

clean:
	rm -rf $(BUILD_DIR) $(TEST_DIR)/__pycache__ *.so