CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:digest pem_read

digest:digest.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

pem_read:pem_read.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm digest
	rm pem_read

