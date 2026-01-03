# Asio Echo Demo

A simple TCP echo server and client demonstrating basic Asio networking functionality.

## Features

- Line-based echo protocol (messages terminated by newline)
- Asynchronous I/O using Asio
- Support for multiple clients (server)
- Cross-platform compatibility (Linux/Windows)

## Building

### Linux (GCC/Clang)

```bash
make
```

This will compile both `asio_echo_server` and `asio_echo_client` executables.

To clean build artifacts:

```bash
make clean
```

### Windows (MSVC)

#### Prerequisites

You need to have Visual Studio installed with the C++ development tools. The build script requires `cl.exe` (the MSVC compiler).

#### Step 1: Open Developer Command Prompt

You must run the build script from a Developer Command Prompt or Developer PowerShell for Visual Studio:

- **Developer Command Prompt for VS**: Search for "x64 Native Tools Command Prompt for VS" or "Developer Command Prompt for VS" in Start menu
- **Developer PowerShell for VS**: Search for "x64 Native Tools Command Prompt for VS" and select the PowerShell option

Alternatively, you can initialize the environment manually:
```cmd
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
```
(Note: Adjust the path based on your Visual Studio installation and edition)

#### Step 2: Build

Navigate to the `demo/asio_echo` directory and run:

```cmd
build_win.bat
```

The script will:
1. Verify `cl.exe` is available
2. Display the compiler version
3. Compile both server and client executables
4. Clean up intermediate files

Success output:
```
========================================
Build successful!
Executables:
  - asio_echo_server.exe
  - asio_echo_client.exe
========================================
```

## Running

### Server

Start the echo server:

**Linux:**
```bash
./asio_echo_server [port]
```

**Windows:**
```cmd
asio_echo_server.exe [port]
```

Default port is `9999`. You can specify a custom port (1-65535).

Example output:
```
Asio Echo Server starting on port 9999...
Server listening on 0.0.0.0:9999
Waiting for client connections...
```

### Client

Connect to the server and send a message:

**Linux:**
```bash
./asio_echo_client [host] [port] [message]
```

**Windows:**
```cmd
asio_echo_client.exe [host] [port] [message]
```

Parameters:
- `host`: Server address (default: 127.0.0.1)
- `port`: Server port (default: 9999)
- `message`: Message to send (if omitted, will prompt for interactive input)

**Example 1: Command-line message**
```bash
asio_echo_client.exe 127.0.0.1 9999 "Hello, World!"
```

**Example 2: Interactive mode**
```bash
asio_echo_client.exe
Enter message (or 'quit' to exit): Hello, Asio!
```

Expected output:
```
Asio Echo Client connecting to 127.0.0.1:9999...
Connected to server
Sent (14 bytes): Hello, World!
Received echo (14 bytes): Hello, World!
Connection closed
```

## Server Output Example

When a client connects and sends a message:

```
Asio Echo Server starting on port 9999...
Server listening on 0.0.0.0:9999
Waiting for client connections...
Client connected from 127.0.0.1:54321
Received (14 bytes): Hello, World!
Echoed (14 bytes)
```

## Dependencies

- **Asio**: Header-only networking library (included as git submodule at `third_party/asio`)
- **C++17**: Required for compilation
- **CMake**: Not required (uses Makefile on Linux, batch script on Windows)
- **Boost**: Not required (using standalone Asio)

## Protocol

The demo uses a simple line-based protocol:
1. Client sends a text message terminated by newline (`\n`)
2. Server reads until newline and echoes the same message back
3. Client receives the echoed message and displays it
4. Client closes the connection after receiving one echo (interactive mode allows multiple messages)

## Troubleshooting

### Windows Build Issues

**"cl.exe not found" error:**
- Ensure you're running from Developer Command Prompt or Developer PowerShell for VS
- Verify Visual Studio C++ tools are installed
- Check that vcvars64.bat has been sourced

**Include path errors:**
- Verify the git submodule is initialized: `git submodule update --init --recursive`
- Check that `third_party/asio/asio/include` directory exists

### Runtime Issues

**Port already in use:**
- Change the port number using the command-line argument
- Ensure no other instance of the server is running

**Connection refused:**
- Verify the server is running before starting the client
- Check firewall settings if connecting across machines