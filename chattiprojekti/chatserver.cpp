#include "chatserver.h"
#include <QThread>
#include <QTcpSocket>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, [=]() {
        QByteArray data = socket->readAll();

    });

    connect(socket, &QTcpSocket::disconnected, [=]() {
        socket->deleteLater();
    });
}
