CC=g++
CFLAGS= -g -Wall
TARGETS = k1_a3.4_main

all: $(TARGETS)

k1_a3.4_main: k1_a3.4_main.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm $(TARGETS)
