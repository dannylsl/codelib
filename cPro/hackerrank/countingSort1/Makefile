CC=gcc
CFLAGS= -g -Wall -o
TARGET= main main2 countingsort4

all:${TARGET}

main:main.c
	${CC} $^ ${CFLAGS} $@

main2:main2.c
	${CC} $^ ${CFLAGS} $@

countingsort4:countingsort4.c
	${CC} $^ ${CFLAGS} $@

.PHONY:clean
clean:
	rm ${TARGET}
