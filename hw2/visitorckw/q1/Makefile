CC = g++
CFLAGS = -std=c++11 -O2

all: main

mainOBJS := main.o Line.o

deps := $(OBJS:%.o=.%.o.d)

main: $(mainOBJS)
	$(CC) -o $@ $(LDFLAGS) $^

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

run: main
	@./main

check: main
	@./main > result.txt

clean:
	rm -f $(mainOBJS) $(deps) *~ main
	rm -rf *.dSYM
	rm -rf .*.o.d
	rm -rf *.txt

-include $(deps)