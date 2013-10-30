CC=gcc
CFLAGS=-Wall -g -O2
LIBS=-lcrypto
 
all: rsa 
	 
rsa: rsa.c
	    $(CC) $(CFLAGS) rsa.c -o $@ $(LIBS)
		 
clean:
	    @rm -f rsa
