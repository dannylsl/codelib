CC=g++
CFLAGS=-g -Wall -o
TARGETS= elist

all:${TARGETS}

elist:list.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}
