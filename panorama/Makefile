CC = arm-linux-g++
CFLAGS = -g -Wall 
TARGETS = matrix.o matrixCatOnArm

all:$(TARGETS)


matrixCatOnArm: matrixCat.cpp matrix.o 
	$(CC) $(CFLAGS) -o $@ $^

matrix.o: matrix.cpp matrix.h
	$(CC) $(CFLAGS) -c $^ 

.PHONY:clean
clean:
	rm $(TARGETS)
