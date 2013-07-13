CC = gcc
CFLAGS = -g -Wall
CLIENT_DIR = client/
SERVER_DIR = serv/
TARGETS = fileClient fileServ

all: $(TARGETS)

fileClient: $(CLIENT_DIR)/fileClient.c
	$(CC) $(CFLAGS) -o $(CLIENT_DIR)$@ $^

fileServ: $(SERVER_DIR)/fileServ.c
	$(CC) $(CFLAGS) -o $(SERVER_DIR)$@ $^ -lpthread
.PHONY:clean
clean:
	rm $(CLIENT_DIR)fileClient
	rm $(SERVER_DIR)fileServ
