CC = g++
CFLAGS = -g -Wall -o
TARGETS = chatserv chatcli  traceroute

all:$(TARGETS)

chatserv: chatServPipe.cpp
	$(CC) $(CFLAGS) $@ $^

chatcli: chatCli.cpp
	$(CC) $(CFLAGS) $@ $^ -lpthread

traceroute: mytraceroute.cpp
	$(CC) $(CFLAGS) $@ $^

.PHONY:clean
clean:
	rm chatserv
	rm chatcli
	rm traceroute
