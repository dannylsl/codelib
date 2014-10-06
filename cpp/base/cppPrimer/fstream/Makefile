CC=g++
CFLAGS=-g -Wall -o
TARGETS=efstream

all:${TARGETS}

efstream:fstream.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}
