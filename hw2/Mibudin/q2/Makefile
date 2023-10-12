
### Settings ###

## The Target Files ##

TARGET_NAME	?= _vector
TARGET_SO_LIB	?= ${TARGET_NAME}$(shell python3-config --extension-suffix)

## The File Structure ##

SRC_DIR	:= .
INC_DIR	:= .
LIB_DIR	:= .
BLD_DIR	:= .
BIN_DIR	:= .

## Compiling ##s

CXX	?= g++
CXX_STD	:= c++17
CXX_INCS	:= $(addprefix -I,${INC_DIR}) \
				$(shell python3 -m pybind11 --includes) \
				$(shell python3-config --includes)
CXX_LIBS	:= $(addprefix -L,${LIB_DIR}) \
				$(shell python3-config --ldflags)
CXX_FLAGS	:= -O2 -Wall -shared -fPIC
ifdef CXX_STD
CXX_FLAGS	+= -std=${CXX_STD}
endif
CXX_COMPILE	:= ${CXX} ${CXX_FLAGS} ${CXX_INCS} ${CXX_LIBS}


### Targets ###

## The Default Target ##

# The default behavior is to build the source code
PHONY	+= default
default: build

## Other Phony Targets ##

# Build the source code
PHONY	+= build
build: ${BIN_DIR}/${TARGET_SO_LIB}

# Run the Python script to test the compiled library
PHONY	+= test
test: build
	python3 -m pytest -v ${SRC_DIR}

# Remove all the built and intermediate files
PHONY	+= clean
clean:
	${RM} "${BIN_DIR}/${TARGET_SO_LIB}"
	${RM} -rd "__pycache__" ".pytest_cache"

## Source Code Targets ##

${BIN_DIR}/${TARGET_SO_LIB}: ${SRC_DIR}/${TARGET_NAME}.cpp | ${BIN_DIR}
	${CXX_COMPILE} $< -o $@

${BIN_DIR}:
	@ mkdir -p $@

## Phony of this Makefile ##

.PHONY: ${PHONY}
