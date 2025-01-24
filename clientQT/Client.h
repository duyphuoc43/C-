#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, QObject *parent = nullptr);
    ~Client();

private slots:
    void onConnected(); // Handle successful connection to the server
    void onTextMessageReceived(const QString &message); // Handle received text messages

private:
    QWebSocket m_webSocket; // WebSocket instance
    QUrl m_url; // URL of the server to connect to
};

#endif // CLIENT_H
