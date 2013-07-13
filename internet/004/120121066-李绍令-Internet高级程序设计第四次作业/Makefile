CC = g++
CFLAGS = -g -Wall -o
TARGETS = chatServio chatCli chatServthread

all:$(TARGETS)

chatServio: chatServIO.cpp
	$(CC) $(CFLAGS) $@ $^

chatServthread: chatServThread.cpp
	$(CC) $(CFLAGS) $@ $^ -lpthread

chatCli: chatCli.cpp
	$(CC) $(CFLAGS) $@ $^ -lpthread

.PHONY:clean
clean:
	rm chatServio
	rm chatServthread
	rm chatCli
