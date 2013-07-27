CC=gcc
CFLAGS= -g -Wall -o
LD=-lssl -lcrypto

ACC=arm-none-linux-gnueabi-gcc
ACFLAGS= -I /usr/local/openssl/include/ -g -Wall -o
ALD=-L /usr/local/openssl/lib/ -static -lssl -lcrypto 
LDFLAGS=-ldl

all:signEnvelop a_signEnvelop unSE a_unSE

signEnvelop:signedAndEnvelop.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

a_signEnvelop:signedAndEnvelop.c
	$(ACC) $(ACFLAGS) $@ $^ $(ALD) $(LDFLAGS)

unSE:unSignEnvelop.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

a_unSE:unSignEnvelop.c
	$(ACC) $(ACFLAGS) $@ $^ $(ALD) $(LDFLAGS)



.PHONY:clean
clean:
	rm signEnvelop a_signEnvelop
	rm unSE a_unSE
