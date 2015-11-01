CC=g++
CFLAGS=-g -Wall
TARGET=rmElem

all:$(TARGET)

rmElem: removeElement.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	rm $(TARGET)
