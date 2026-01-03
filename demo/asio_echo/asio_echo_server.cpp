#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class EchoSession : public std::enable_shared_from_this<EchoSession> {
public:
    explicit EchoSession(tcp::socket socket)
        : socket_(std::move(socket)) {
    }

    void start() {
        do_read();
    }

private:
    void do_read() {
        auto self(shared_from_this());
        asio::async_read_until(socket_, buffer_, '\n',
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    // 读取完整行（包含换行符）
                    std::istream is(&buffer_);
                    std::string line;
                    std::getline(is, line);
                    // getline 会去掉换行符，需要重新添加
                    if (length > 0 && line.empty()) {
                        line = "\n";
                    } else {
                        line += "\n";
                    }

                    std::cout << "Received (" << length << " bytes): " << line;

                    do_write(line);
                } else if (ec == asio::error::eof) {
                    std::cout << "Client disconnected\n";
                } else {
                    std::cerr << "Read error: " << ec.message() << "\n";
                }
            });
    }

    void do_write(const std::string& message) {
        auto self(shared_from_this());
        asio::async_write(socket_, asio::buffer(message),
            [this, self, message](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Echoed (" << length << " bytes)\n";
                    do_read();  // 继续读取下一条消息
                } else {
                    std::cerr << "Write error: " << ec.message() << "\n";
                }
            });
    }

    tcp::socket socket_;
    asio::streambuf buffer_;
};

class EchoServer {
public:
    EchoServer(asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
            [this](std::error_code ec, tcp::socket socket) {
                if (!ec) {
                    auto remote_endpoint = socket.remote_endpoint();
                    std::cout << "Client connected from "
                              << remote_endpoint.address().to_string()
                              << ":" << remote_endpoint.port() << "\n";

                    std::make_shared<EchoSession>(std::move(socket))->start();
                } else {
                    std::cerr << "Accept error: " << ec.message() << "\n";
                }
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    try {
        unsigned short port = 9999;

        if (argc > 1) {
            port = std::stoi(argv[1]);
            if (port <= 0 || port > 65535) {
                std::cerr << "Invalid port number: " << argv[1] << "\n";
                std::cerr << "Usage: " << argv[0] << " [port]\n";
                return 1;
            }
        }

        std::cout << "Asio Echo Server starting on port " << port << "...\n";

        asio::io_context io_context;
        EchoServer server(io_context, port);

        std::cout << "Server listening on 0.0.0.0:" << port << "\n";
        std::cout << "Waiting for client connections...\n";

        io_context.run();

        std::cout << "Server stopped\n";
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
