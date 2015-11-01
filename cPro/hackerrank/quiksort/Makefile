CC=gcc
CFLAGS=-g -Wall -o
TARGETS=main main2 runtime

all:${TARGETS}

main:main.c
	${CC} $^ ${CFLAGS} $@
main2:main2.c
	${CC} $^ ${CFLAGS} $@
runtime:runtime.c
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGETS}
