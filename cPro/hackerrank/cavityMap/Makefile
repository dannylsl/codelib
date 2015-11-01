CC=gcc
CFLAGS=-g -Wall -o
TARGET=cavityMap

all:${TARGET}

cavityMap:cavityMap.c
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGET}
