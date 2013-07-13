CC=gcc
CFLAGS=-g -Wall -o
LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LDFLAGS=-ldl

all:cli serv

cli:cli.c
	$(CC) $(CFLAGS) $@ $^ $(LD) $(LDFLAGS) 
serv:serv.c
	$(CC) $(CFLAGS) $@ $^ $(LD) $(LDFLAGS)

.PHONY:clean
clean:
	rm cli
	rm serv

