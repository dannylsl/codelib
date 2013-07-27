CC=gcc
ACC=arm-none-linux-gnueabi-gcc
CFLAGS= -I /usr/local/openssl/include/ -g -Wall -o
ALD=-L/usr/local/openssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:serv a_serv

serv:serv.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

a_serv:serv.c
	$(ACC) $(CFLAGS) $@ $^ $(ALD) 

.PHONY:clean
clean:
	rm serv
	rm a_serv
