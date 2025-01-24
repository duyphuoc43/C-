#include "Client.h"

Client::Client(const QUrl &url, QObject *parent)
    : QObject(parent),
    m_url(url)
{
    // Connect WebSocket signals to the appropriate slots
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);

    // Start connecting to the server
    qDebug() << "Connecting to server at:" << url.toString();
    m_webSocket.open(m_url);
}

Client::~Client()
{
    // Close the connection on destruction
    m_webSocket.close();
    qDebug() << "Client disconnected.";
}

void Client::onConnected()
{
    // Log when the client successfully connects to the server
    qDebug() << "Connected to the server.";

    // Send a message to the server after connecting
    m_webSocket.sendTextMessage(QStringLiteral("Hello, Server!"));
}

void Client::onTextMessageReceived(const QString &message)
{
    // Handle received text messages from the server
    qDebug() << "Message from server:" << message;
}
