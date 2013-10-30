CC=gcc
CFLAGS=-Wall -g -o  
LIBS=-lcrypto
 
all: read_prikey_decode
	 
read_prikey_decode: read_prikey_decode.c
	    $(CC) $(CFLAGS)  $@ $^  $(LIBS)
		 
clean:
	    @rm -f read_prikey_decode
