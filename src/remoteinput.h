#ifndef REMOTEINPUT_H
#define REMOTEINPUT_H

#include <QList>
#include <QPointer>
#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSignalMapper>
#include "input.h"

/// User input from remote
class RemoteInput : public Input
{
    Q_OBJECT
public:
    explicit RemoteInput(QObject *parent);
    ~RemoteInput();

    bool isServer() { return server; }

    /// Call remote method in JSON format
    void send(const QString &method, const QJsonObject &params = QJsonObject());

signals:
    /**
     * @brief emitted when client list changed
     * @param list of ips of clients
     */
    void newClientList(const QList<QString> &list);
    /// emitted when unable to setup server
    void serverError();
    /// emitted when connection fails
    void connectError();
    /// emitted when connection accepted by both side
    void hello();

public slots:
    /// setup a server listening to `addr`
    void setupServer(const QString &addr);
    /// accept a client to be working socket `socket`
    void acceptClient(int index);
    /// delete server and socket
    void reset();
    /// connect to server
    void connectToServer(const QString &addr);

private slots:
    void newClient();
    void clientClosed(QObject *_socket);
    /// When data blocks received
    void onData();

private:
    void setupSocket();

    void newClientListEmitter();

    QPointer<QTcpServer> server;
    QList< QPointer<QTcpSocket> > pendingSockets;

    /// The socket that is working, no longer as server or client
    QPointer<QTcpSocket> socket;

    /// transfer disconnection signal
    QSignalMapper *closeMapper;

    QByteArray dataReceived;
};

#endif // REMOTEINPUT_H
