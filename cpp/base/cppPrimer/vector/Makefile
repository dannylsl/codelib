CC=g++
CFLAGS=-g -Wall -o
TARGETS= 1evector  2vector_iterator

all:${TARGETS}

1evector:vector.cpp
	${CC} $^ ${CFLAGS} $@
2vector_iterator:vector_iterator.cpp
	${CC} $^ ${CFLAGS} $@

.PHNOY:clean
clean:
	rm ${TARGETS}
