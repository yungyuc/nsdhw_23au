CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Wpedantic

BUILD_DIR := build
BIN := $(BUILD_DIR)/hw2_q1

SRCS := $(wildcard src/*.cpp)

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

-include $(DEPS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: run
run: $(BIN)
	@$(BIN)

.PHONY: check
check: $(BIN)
	@$(BIN) > result.txt
