#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <iostream>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSocketServer {
public:
    WebSocketServer(short port);
    void run();

private:
    void do_accept();
    void on_session(tcp::socket socket);

    net::io_context ioc_;
    tcp::acceptor acceptor_;
};

#endif // WEBSOCKET_SERVER_H
