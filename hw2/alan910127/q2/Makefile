CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -Wpedantic -fPIC
LDFLAGS := -shared
INCLUDES := $(shell python3 -m pybind11 --includes)
SO_EXT := $(shell python3-config --extension-suffix)

BUILD_DIR := build
SO_FILE := _vector$(SO_EXT)
LIB := $(BUILD_DIR)/$(SO_FILE)

SRCS := $(wildcard src/*.cpp)

OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(SO_FILE)

$(SO_FILE): $(LIB)
	@mkdir -p $(@D)
	cp $< $@

$(LIB): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(INCLUDES)

-include $(DEPS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@ $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(SO_FILE)
