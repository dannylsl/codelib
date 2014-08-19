CC=gcc
CFLAGS=-g -Wall -o
TARGETS=main

all:${TARGETS}

main:main.c
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGETS}
