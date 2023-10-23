OS := $(shell cat /etc/os-release | grep -oP '(?<=^ID=).+' | tr -d '"')
ifeq (${OS},ubuntu)
	SYSFLAG := UBUNTU
else ifeq (${OS},arch)
	SYSFLAG := ARCHLINUX
else
	SYSFLAG := OTHER
endif

CXX := g++
CXXFLAGS := -std=gnu++17 -O3 -Wall -fPIC -D$(SYSFLAG)

LDFLAGS := -shared
ifeq (${OS},arch)
	LDFLAGS += -L/opt/intel/oneapi/mkl/latest/lib/intel64 -lmkl_rt
else ifeq (${OS},ubuntu)
	LDFLAGS += -lblas
endif

INCLUDES := -Iextern/pybind11/include $(shell python3-config --includes) -Iinclude
ifeq (${OS},arch)
	INCLUDES += -I/opt/intel/mkl/include
endif

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

TARGET := _matrix$(shell python3-config --extension-suffix)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	python3 -m pytest -v 
