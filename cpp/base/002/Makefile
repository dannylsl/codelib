CC=g++
CFLAGS=-g -Wall
TARGET=cinEof

all:$(TARGET)

cinEof:cinEof.cpp
	$(CC) $(CFLAGS) $^ -o $@ 

.PHONY:clean
clean:
	rm $(TARGET)
