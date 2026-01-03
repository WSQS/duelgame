# Makefile for Asio Echo Demo
# Build targets: all (default), server, client, clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
ASIO_INCLUDE = -I../../third_party/asio/asio/include

# Source files
SERVER_SRC = asio_echo_server.cpp
CLIENT_SRC = asio_echo_client.cpp

# Executables
SERVER_BIN = asio_echo_server
CLIENT_BIN = asio_echo_client

# Default target: build both server and client
all: server client

# Build server executable
server: $(SERVER_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) $(ASIO_INCLUDE) -o $(SERVER_BIN) $(SERVER_SRC)

# Build client executable
client: $(CLIENT_BIN)

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) $(ASIO_INCLUDE) -o $(CLIENT_BIN) $(CLIENT_SRC)

# Clean build artifacts
clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
	@echo "Cleaned build artifacts"

# Phony targets
.PHONY: all server client clean