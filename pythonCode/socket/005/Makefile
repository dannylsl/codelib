CC=gcc
CFLAGS=-g -Wall -o
LD = -lssl -lcrypto

all:caClient

caClient:caClient.c
	$(CC) $(CFLAGS) $@ $^ $(LD)

.PHONY:clean
clean:
	rm caClient
