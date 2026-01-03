#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        std::string host = "127.0.0.1";
        unsigned short port = 9999;
        std::string message;

        // 解析命令行参数
        if (argc >= 2) {
            host = argv[1];
        }
        if (argc >= 3) {
            port = std::stoi(argv[2]);
            if (port <= 0 || port > 65535) {
                std::cerr << "Invalid port number: " << argv[2] << "\n";
                std::cerr << "Usage: " << argv[0] << " [host] [port] [message]\n";
                return 1;
            }
        }
        if (argc >= 4) {
            message = argv[3];
        }

        std::cout << "Asio Echo Client connecting to " << host << ":" << port << "...\n";

        asio::io_context io_context;

        // 解析服务器地址
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, std::to_string(port));

        // 连接服务器
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        std::cout << "Connected to server\n";

        // 获取要发送的消息
        if (message.empty()) {
            std::cout << "Enter message (or 'quit' to exit): ";
            std::getline(std::cin, message);
        }

        // 确保消息以换行符结尾
        if (!message.empty() && message.back() != '\n') {
            message += "\n";
        }

        // 发送消息
        std::size_t bytes_sent = asio::write(socket, asio::buffer(message));
        std::cout << "Sent (" << bytes_sent << " bytes): " << message;

        // 接收回显
        asio::streambuf buffer;
        std::size_t bytes_received = asio::read_until(socket, buffer, '\n');
        std::istream is(&buffer);
        std::string echo;
        std::getline(is, echo);
        // getline 会去掉换行符，需要重新添加
        if (bytes_received > 0 && echo.empty()) {
            echo = "\n";
        } else {
            echo += "\n";
        }

        std::cout << "Received echo (" << bytes_received << " bytes): " << echo;

        // 关闭连接
        socket.close();
        std::cout << "Connection closed\n";

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}