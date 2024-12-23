#include <QGuiApplication>
#include <QQmlApplicationEngine>

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreationFailed,
//         &app,
//         []() { QCoreApplication::exit(-1); },
//         Qt::QueuedConnection);
//     engine.loadFromModule("AppTest", "Main");

//     return app.exec();
// }
#include "WebSocketServer.h"
#include "WebSocketClient.h"
#include <thread>

int main() {
    // Chạy server trong một luồng riêng
    std::thread server_thread([]() {
        WebSocketServer server(8081);
        server.run();
    });

    // Chạy client
    WebSocketClient client("localhost", "8081");
    client.run();

    server_thread.join();
    return 0;
}

