CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:encrypted

encrypted:encrypted.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm encrypted

