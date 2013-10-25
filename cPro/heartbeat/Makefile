CC=gcc
CFLAGS=-g -Wall -o

all:heartbeat

heartbeat:heartbeat.c
	$(CC) $(CFLAGS) $@ $^


.PHONY:clean
clean:
	rm heartbeat
