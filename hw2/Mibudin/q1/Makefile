
### Settings ###

## The Target Files ##

EXECUTABLE	?= hw2-q1
OUTPUT_FILE	?= result.txt

## The File Structure ##

SRC_DIR	:= .
INC_DIR	:= .
LIB_DIR	:= .
BLD_DIR	:= build
OBJ_DIR	:= ${BLD_DIR}/obj
BIN_DIR	:= ${BLD_DIR}/bin
OUT_DIR	:= .

## Compiling ##s

CXX	?= g++
CXX_STD	:= c++17
CXX_INCS	:= $(addprefix -I,${INC_DIR})
CXX_LIBS	:= $(addprefix -L,${LIB_DIR})
CXX_FLAGS	:= -O2 -Wall
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
build: ${BIN_DIR}/${EXECUTABLE}

# Run the executable file
PHONY	+= run
run: build
	"./${BIN_DIR}/${EXECUTABLE}"

# Run the executable file and redirect `stdin` and `stderr` to the output file
PHONY	+= check
check: build
	"./${BIN_DIR}/${EXECUTABLE}" > "${OUT_DIR}/${OUTPUT_FILE}" 2>&1

# Remove all the built and intermediate files
PHONY	+= clean
clean:
	${RM} -rd "${BLD_DIR}"
	${RM} "${BIN_DIR}/${EXECUTABLE}"
	${RM} "${OUT_DIR}/${OUTPUT_FILE}"

## Source Code Targets ##

${BIN_DIR}/${EXECUTABLE}: ${OBJ_DIR}/main.o ${OBJ_DIR}/line.o | ${BIN_DIR}
	${CXX_COMPILE} $^ -o $@

${OBJ_DIR}/main.o: ${SRC_DIR}/main.cpp ${INC_DIR}/line.hpp | ${OBJ_DIR}
	${CXX_COMPILE} -c $< -o $@

${OBJ_DIR}/line.o: ${SRC_DIR}/line.cpp ${INC_DIR}/line.hpp | ${OBJ_DIR}
	${CXX_COMPILE} -c $< -o $@

${OBJ_DIR} ${BIN_DIR}:
	@ mkdir -p $@

## Phony of this Makefile ##

.PHONY: ${PHONY}
