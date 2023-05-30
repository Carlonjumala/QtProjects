#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // CHATSERVER_H
