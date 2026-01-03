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
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    int port = DEFAULT_PORT;

    // 解析命令行参数
    if (argc > 1) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "Invalid port number: %s\n", argv[1]);
            fprintf(stderr, "Usage: %s [port]\n", argv[0]);
            return 1;
        }
    }

    printf("TCP Echo Server starting on port %d...\n", port);

    // 创建 socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket() failed");
        return 1;
    }

    // 设置 socket 选项，允许地址重用
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt() failed");
        close(server_fd);
        return 1;
    }

    // 绑定地址和端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind() failed");
        close(server_fd);
        return 1;
    }

    // 监听连接
    if (listen(server_fd, 1) < 0) {
        perror("listen() failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on 0.0.0.0:%d\n", port);
    printf("Waiting for a client connection...\n");

    // 接受客户端连接
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept() failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected from %s:%d\n",
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    // 接收数据并回显
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received < 0) {
            perror("recv() failed");
            break;
        } else if (bytes_received == 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Received (%zd bytes): %s", bytes_received, buffer);

        // 回显数据（保持换行符）
        ssize_t bytes_sent = send(client_fd, buffer, bytes_received, 0);
        if (bytes_sent < 0) {
            perror("send() failed");
            break;
        } else if (bytes_sent != bytes_received) {
            fprintf(stderr, "Warning: sent %zd bytes, expected %zd bytes\n",
                    bytes_sent, bytes_received);
        }

        printf("Echoed (%zd bytes)\n", bytes_sent);

        // 如果收到 "quit" 命令，退出
        if (strncmp(buffer, "quit", 4) == 0) {
            printf("Received quit command, shutting down...\n");
            break;
        }
    }

    // 关闭连接
    close(client_fd);
    close(server_fd);
    printf("Server stopped\n");

    return 0;
}