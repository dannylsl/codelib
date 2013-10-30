CC=gcc
CFLAGS=-g -Wall -o
#LD=-L/usr/local/ssl/lib/ -lssl -lcrypto 
LD=-lssl -lcrypto
#LDFLAGS=-ldl

all:signed_data decrypt_sign

signed_data:signed_data.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 
decrypt_sign:decrypt_sign.c
	$(CC) $(CFLAGS) $@ $^ $(LD) 

.PHONY:clean
clean:
	rm signed_data
	rm decrypt_sign
