CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:signed_and_enveloped

signed_and_enveloped:signed_and_enveloped.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm signed_and_enveloped

