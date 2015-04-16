CC=g++
CFLAGS=-g -Wall
TARGETS=main Object.o

all: $(TARGETS)

Object.o:Object.cpp Object.h
	$(CC) $(CFLAGS) -c $^

main:Object.o main.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm main *.o *.gch
