#include <QDebug>
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include "const.h"
#include "remoteinput.h"

RemoteInput::RemoteInput(QObject *parent)
    : Input(parent), server(0), socket(0), closeMapper(new QSignalMapper(this)), dataReceived("") {}

RemoteInput::~RemoteInput()
{
    reset();
    delete closeMapper;
}

void RemoteInput::setupServer(const QString &addr)
{
    Q_ASSERT(! server);
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newClient()));

    bool success = server->listen(QHostAddress(addr), PORT);
    if (! success)
    {
        emit serverError();
        return;
    }
}

void RemoteInput::acceptClient(int index)
{
    for (int i = 0; i < pendingSockets.size(); i++)
        if (i != index)
            pendingSockets[i]->close();
    socket = pendingSockets[index];
    pendingSockets.clear();
    setupSocket();
    send("Hello");
}

void RemoteInput::reset()
{
    if (socket)
    {
        delete socket;
        socket = 0;
    }
    if (server)
    {
        delete server;
        server = 0;
    }
    for (int i = 0; i < pendingSockets.size(); i++)
        if (pendingSockets[i])
        {
            delete pendingSockets[i];
            pendingSockets[i] = 0;
        }
    pendingSockets.clear();
}

void RemoteInput::connectToServer(const QString &addr)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(addr), PORT);;
    setupSocket();
}

void RemoteInput::newClient()
{
    while (server->hasPendingConnections())
    {
        QTcpSocket *connection = server->nextPendingConnection();
        pendingSockets.push_back(connection);
        connect(connection, SIGNAL(disconnected()), closeMapper, SLOT(map(QObject*)));
        closeMapper->setMapping(connection, connection);
        connect(closeMapper, SIGNAL(mapped(QObject*)), this, SLOT(clientClosed(QObject*)));
    }
    newClientListEmitter();
}

// Since we are in the same thread with ui, there is no need to worry that something
// is triggered in ui when updating socket list.
void RemoteInput::clientClosed(QObject *socket)
{
    for (int i = 0; i < pendingSockets.size(); i++)
        if (pendingSockets[i] == socket)
        {
            pendingSockets.removeAt(i);
            break;
        }
    newClientListEmitter();
}

void RemoteInput::onData()
{
    QByteArray arr = socket->readAll();
    qDebug() << "received " + arr;
}

void RemoteInput::setupSocket()
{
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(connectError()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onData()));
}

void RemoteInput::newClientListEmitter()
{
    QList<QString> ret;
    for (int i = 0; i < pendingSockets.size(); i++)
        ret.push_back(pendingSockets[i]->peerAddress().toString());
    emit newClientList(ret);
}

void RemoteInput::send(const QString &method, const QJsonObject &params)
{
    QJsonObject obj;
    obj["method"] = method;
    obj["params"] = params;
    QByteArray raw = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    qDebug() << "sent " << raw;
    socket->write(raw);
}
