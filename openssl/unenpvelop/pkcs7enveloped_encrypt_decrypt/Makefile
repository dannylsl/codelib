CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:signedAndEnveloped cert_pk_test

signedAndEnveloped:signedAndEnveloped.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

cert_pk_test:cert_pk_test.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm signedAndEnveloped
