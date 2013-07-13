CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:cli serv

cli:cli.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 
serv:serv.c
	$(CC) $(CFLAGS) $@ $^ $(LD)

.PHONY:clean
clean:
	rm cli
	rm serv

