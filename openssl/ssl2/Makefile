# Generated automatically from Makefile.in by configure.
CC=gcc
CFLAGS=-g -I/usr/include  -Wall 
LD=-L/usr/lib  -lssl -lcrypto

all: cli serv 

cli:
	$(CC) $(CFLAGS) cli.c -o cli #$(LD)
serv:
	$(CC) $(CFLAGS) serv.c -o serv #$(LD)
clean:    
	rm cli 
	rm serv
