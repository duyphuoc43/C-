#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class WebSocketClient {
public:
    WebSocketClient(const std::string& host, const std::string& port);
    void run();

private:
    std::string host_;
    std::string port_;
    net::io_context ioc_;
    websocket::stream<tcp::socket> ws_;
};

#endif // WEBSOCKET_CLIENT_H
