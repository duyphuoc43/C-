#include "Server.h"

Server::Server(QObject *parent)
    : QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                  QWebSocketServer::NonSecureMode, this))
{
    // Start the WebSocket server on port 1234
    if (m_server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server is listening on port 1234";
        connect(m_server, &QWebSocketServer::newConnection, this, &Server::onNewConnection);
    } else {
        qDebug() << "Failed to start the server.";
    }
}

Server::~Server()
{
    // Clean up resources
    m_server->close();
    qDeleteAll(m_clients);
    qDebug() << "Server stopped.";
}

void Server::onNewConnection()
{
    QWebSocket *client = m_server->nextPendingConnection();

    // Add the new client to the list
    m_clients.append(client);

    qDebug() << "New connection from:" << client->peerAddress().toString();

    // Connect signals for the new client
    connect(client, &QWebSocket::textMessageReceived, this, &Server::onTextMessageReceived);
    connect(client, &QWebSocket::binaryMessageReceived, this, &Server::onBinaryMessageReceived);
    connect(client, &QWebSocket::disconnected, this, &Server::onDisconnected);
}

void Server::onTextMessageReceived(const QString &message)
{
    // Handle text messages
    qDebug() << "Received text message:" << message;

    // Echo the message back to the client
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        client->sendTextMessage(QString("Echo: %1").arg(message));
    }
}

void Server::onBinaryMessageReceived(const QByteArray &data)
{
    // Handle binary messages
    qDebug() << "Received binary message of size:" << data.size();
}

void Server::onDisconnected()
{
    // Handle client disconnections
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        qDebug() << "Client disconnected:" << client->peerAddress().toString();

        m_clients.removeAll(client); // Remove the client from the list
        client->deleteLater(); // Clean up the client object
    }
}
