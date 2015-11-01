CC=g++
CFLAGS=-g -Wall -o
TARGETS=gameofrotate gameofrotate_opt

all:${TARGETS}

gameofrotate:gameofrotate.cpp
	${CC} $^ ${CFLAGS} $@

gameofrotate_opt:gameofrotate_opt.cpp
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGETS}
