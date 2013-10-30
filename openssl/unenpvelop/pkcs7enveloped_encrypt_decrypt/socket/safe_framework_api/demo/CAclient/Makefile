CC=gcc
CFLAGS=-g -Wall -o
LD = -lssl -lcrypto

all:caClient reqtest

caClient:caClient.c
	$(CC) $(CFLAGS) $@ $^ $(LD)
reqtest:reqtest.c
	$(CC) $(CFLAGS) $@ $^ $(LD)

.PHONY:clean
clean:
	rm caClient
	rm reqtest
