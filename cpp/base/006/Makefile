CC=g++
CFLAGS=-g -Wall
TARGETS=main List.o

all: $(TARGETS)

List.o:List.cpp List.h
	$(CC) $(CFLAGS) -c $^

main:List.o main.cpp
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm main *.o *.gch
