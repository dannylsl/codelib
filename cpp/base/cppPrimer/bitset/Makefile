CC=g++
CFLAGS=-g -Wall -o
TARGETS= ebitset

all:${TARGETS}

ebitset:bitset.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}
