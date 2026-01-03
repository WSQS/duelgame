# Makefile for TCP Echo Demo
# Build targets: all (default), server, client, clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
LDFLAGS =

# Source files
SERVER_SRC = tcp_echo_server.c
CLIENT_SRC = tcp_echo_client.c

# Executables
SERVER_BIN = tcp_echo_server
CLIENT_BIN = tcp_echo_client

# Default target: build both server and client
all: server client

# Build server executable
server: $(SERVER_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $(SERVER_BIN) $(SERVER_SRC) $(LDFLAGS)

# Build client executable
client: $(CLIENT_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC) $(LDFLAGS)

# Clean build artifacts
clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
	@echo "Cleaned build artifacts"

# Phony targets
.PHONY: all server client clean