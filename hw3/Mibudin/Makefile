### Settings ###

## The Target Files ##

TARGET_NAME	?= _matrix
TARGET_SO_LIB	?= ${TARGET_NAME}$(shell python3-config --extension-suffix)

## The File Structure ##

SRC_DIR	:= .
INC_DIR	:= .
LIB_DIR	:= .
BLD_DIR	:= build
OBJ_DIR	:= ${BLD_DIR}/obj
BIN_DIR	:= .

## Compiling ##

CXX	?= g++
CXX_STD	:= c++17
CXX_INCS	:= $(addprefix -I,${INC_DIR}) \
				$(shell python3-config --includes)
CXX_LIBS	:= $(addprefix -L,${LIB_DIR}) \
				$(shell python3-config --ldflags)
CXX_FLAGS	:= -O3 -Wall -shared -fPIC
ifdef CXX_STD
CXX_FLAGS	+= -std=${CXX_STD}
endif
CXX_COMPILE	:= ${CXX} ${CXX_FLAGS} ${CXX_INCS} ${CXX_LIBS}

# Workaround for cmake + MKL in conda
MKL_LIB_DIR=/usr/lib/x86_64-linux-gnu
MKL_LIBS	:= ${MKL_LIB_DIR}/libmkl_def.so$\
				:${MKL_LIB_DIR}/libmkl_avx2.so$\
				:${MKL_LIB_DIR}/libmkl_core.so$\
				:${MKL_LIB_DIR}/libmkl_intel_lp64.so$\
				:${MKL_LIB_DIR}/libmkl_sequential.so
export LD_PRELOAD	:= ${MKL_LIBS}


### Targets ###

## The Default Target ##

# The default behavior is to build the source code
.PHONY: default
default: build

## Other Phony Targets ##

# Build the source code
.PHONY: build
build: ${BIN_DIR}/${TARGET_SO_LIB}

# Run the Python script to test the compiled library
.PHONY: test
test: build
	python3 -m pytest -sv ${SRC_DIR}

# Remove all the built and intermediate files
.PHONY: clean
clean:
	${RM} "${BIN_DIR}/${TARGET_SO_LIB}"
	${RM} -rd "${BLD_DIR}"
	${RM} -rd "__pycache__" ".pytest_cache"

## Source Code Targets ##

${BIN_DIR}/${TARGET_SO_LIB}: \
		${OBJ_DIR}/${TARGET_NAME}.o ${OBJ_DIR}/matrix.o | ${BIN_DIR}
	${CXX_COMPILE} $^ -o $@

${OBJ_DIR}/${TARGET_NAME}.o: \
		${SRC_DIR}/${TARGET_NAME}.cpp ${INC_DIR}/${TARGET_NAME}.hpp \
		${INC_DIR}/matrix.hpp | ${OBJ_DIR}
	${CXX_COMPILE} -c $< -o $@

${OBJ_DIR}/matrix.o: ${SRC_DIR}/matrix.cpp ${INC_DIR}/matrix.hpp | ${OBJ_DIR}
	${CXX_COMPILE} -c $< -o $@

${BIN_DIR} ${OBJ_DIR}:
	@ mkdir -p $@
