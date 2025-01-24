#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Client.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("clientQT", "Main");
    // URL of the WebSocket server
    QUrl serverUrl(QStringLiteral("ws://0.0.0.0:1234"));

    // Create the WebSocket client and connect to the server
    Client client(serverUrl);

    return app.exec();
}
