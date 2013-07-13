CC=gcc
CFLAGS=-g -Wall -o 
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:genApply deApply reqtest

genApply:genApply.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 
deApply:deApply.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 
reqtest:reqtest.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm genApply
	rm deApply
	rm reqtest
