CC=g++
CFLAGS=-g -Wall -o

all:cli serv

cli:cli.cpp
	$(CC) $(CFLAGS) $@ $^  
serv:serv.cpp
	$(CC) $(CFLAGS) $@ $^ 

.PHONY:clean
clean:
	rm cli
	rm serv

