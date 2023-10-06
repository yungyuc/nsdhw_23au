CC = g++
CFLAGS = -std=c++11 -O2

all: main

OBJS := main.o Line.o

deps := $(OBJS:%.o=.%.o.d)

main: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c -MMD -MF .$@.d $<

run: main
	@./main

check: main
	@./main > result.txt

clean:
	rm -f $(OBJS) $(deps) *~ main
	rm -rf *.dSYM
	rm -rf *.txt

-include $(deps)