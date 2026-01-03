#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define DEFAULT_PORT 8888
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_sent, bytes_received;
    char *server_ip = "127.0.0.1";
    int port = DEFAULT_PORT;
    char *message = NULL;

    // 解析命令行参数
    // 用法: ./client [server_ip] [port] [message]
    if (argc >= 2) {
        server_ip = argv[1];
    }
    if (argc >= 3) {
        port = atoi(argv[2]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "Invalid port number: %s\n", argv[2]);
            fprintf(stderr, "Usage: %s [server_ip] [port] [message]\n", argv[0]);
            return 1;
        }
    }
    if (argc >= 4) {
        message = argv[3];
    }

    printf("TCP Echo Client connecting to %s:%d...\n", server_ip, port);

    // 创建 socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket() failed");
        return 1;
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton() failed");
        close(client_fd);
        return 1;
    }

    // 连接服务器
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect() failed");
        close(client_fd);
        return 1;
    }

    printf("Connected to server\n");

    // 获取要发送的消息
    if (message == NULL) {
        printf("Enter message (or 'quit' to exit): ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets() failed");
            close(client_fd);
            return 1;
        }
        message = buffer;
    }

    // 发送消息
    bytes_sent = send(client_fd, message, strlen(message), 0);
    if (bytes_sent < 0) {
        perror("send() failed");
        close(client_fd);
        return 1;
    }

    printf("Sent (%zd bytes): %s", bytes_sent, message);

    // 接收回显
    memset(buffer, 0, BUFFER_SIZE);
    bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("recv() failed");
        close(client_fd);
        return 1;
    } else if (bytes_received == 0) {
        printf("Server closed connection\n");
        close(client_fd);
        return 0;
    }

    printf("Received echo (%zd bytes): %s", bytes_received, buffer);

    // 关闭连接
    close(client_fd);
    printf("Connection closed\n");

    return 0;
}