CC=gcc
CFLAGS=-g -Wall -o
TARGETS=gameofrotate

all:${TARGETS}

gameofrotate:gameofrotate.c
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGETS}
