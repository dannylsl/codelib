CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:data

data:data.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm data

