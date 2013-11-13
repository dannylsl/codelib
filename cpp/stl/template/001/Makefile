CC=g++
CFLAGS= -g -Wall
TARGETS = basic

all: $(TARGETS)

basic: basic.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm $(TARGETS)
