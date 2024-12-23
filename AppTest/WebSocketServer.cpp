#include "WebSocketServer.h"

WebSocketServer::WebSocketServer(short port)
    : acceptor_(ioc_, tcp::endpoint(tcp::v4(), port)) {}

void WebSocketServer::run() {
    std::cout << "WebSocket Server running on ws://localhost:" << acceptor_.local_endpoint().port() << "\n";
    do_accept();
    ioc_.run();
}

void WebSocketServer::do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::thread(&WebSocketServer::on_session, this, std::move(socket)).detach();
        }
        do_accept();
    });
}

void WebSocketServer::on_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();

        for (;;) {
            beast::flat_buffer buffer;
            ws.read(buffer);
            ws.text(ws.got_text());
            ws.write(buffer.data());
        }
    } catch (beast::system_error const& se) {
        if (se.code() != websocket::error::closed) {
            std::cerr << "Session error: " << se.code().message() << "\n";
        }
    } catch (std::exception const& e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

