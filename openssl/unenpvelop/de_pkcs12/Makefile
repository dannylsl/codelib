CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:de_pkcs12 read_pk12

de_pkcs12:de_pkcs12.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 
read_pk12:read_pk12.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm de_pkcs12
	rm read_pk12

