CC=g++
CFLAGS=-g -Wall
TARGET=typeSize

all:$(TARGET)

typeSize: typeSize.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	rm $(TARGET)
