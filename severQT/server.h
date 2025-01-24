#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr); // Constructor
    ~Server(); // Destructor

private slots:
    void onNewConnection(); // Handle new client connections
    void onTextMessageReceived(const QString &message); // Handle text messages
    void onBinaryMessageReceived(const QByteArray &data); // Handle binary messages
    void onDisconnected(); // Handle client disconnections

private:
    QWebSocketServer *m_server; // WebSocket server instance
    QList<QWebSocket *> m_clients; // List of connected clients
};

#endif // SERVER_H
