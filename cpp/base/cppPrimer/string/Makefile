CC=g++
CFLAGS=-g -Wall -o
TARGETS= estring

all:${TARGETS}

estring:string.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}
