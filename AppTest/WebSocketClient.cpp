#include "WebSocketClient.h"

WebSocketClient::WebSocketClient(const std::string& host, const std::string& port)
    : host_(host), port_(port), ws_(ioc_) {}

void WebSocketClient::run() {
    try {
        tcp::resolver resolver(ioc_);
        auto const results = resolver.resolve(host_, port_);
        net::connect(ws_.next_layer(), results.begin(), results.end());
        ws_.handshake(host_, "/");

        std::cout << "Connected to WebSocket server at ws://" << host_ << ":" << port_ << "\n";

        std::string message;
        while (std::getline(std::cin, message)) {
            ws_.write(net::buffer(message));
            beast::flat_buffer buffer;
            ws_.read(buffer);
            std::cout << "Server response: " << beast::make_printable(buffer.data()) << "\n";
        }

        // Gửi tín hiệu đóng
        ws_.close(websocket::close_code::normal);
    } catch (beast::system_error const& se) {
        if (se.code() != websocket::error::closed) {
            std::cerr << "Client error: " << se.code().message() << "\n";
        }
    } catch (std::exception const& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
}

