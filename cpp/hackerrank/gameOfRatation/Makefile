CC=g++
CFLAGS=-g -Wall -o
TARGETS=gameofrotate

all:${TARGETS}

gameofrotate:gameofrotate.cpp
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGETS}
