CC=g++
CFLAGS= -g -Wall -o
TARGETS= gemstone

all:${TARGETS}

gemstone: gemstone.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}

