#CC=gcc
CC=arm-none-linux-gnueabi-gcc
#CFLAGS= -static -g -Wall -o
CFLAGS= -I /usr/local/openssl/include -g -Wall -o
LD=-L /usr/local/openssl/lib/ -lssl -lcrypto 
#LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:data

data:data.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm data

