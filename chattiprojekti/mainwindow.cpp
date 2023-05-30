#include "chatserver.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Alustetaan UI componentit projektiin
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    chatDisplay = new QTextEdit(centralWidget);
    chatDisplay->setReadOnly(true);

    inputField = new QLineEdit(centralWidget);

    QPushButton *sendButton = new QPushButton("Send", centralWidget);
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);

    layout->addWidget(chatDisplay);
    layout->addWidget(inputField);
    layout->addWidget(sendButton);

    // Luodaan toolbar
    QToolBar *toolbar = new QToolBar(this);
    QAction *action1 = toolbar->addAction("Tool 1");
    QAction *action2 = toolbar->addAction("Tool 2");

    // Lisätään toolbaari ikkunaan
    addToolBar(toolbar);

    setCentralWidget(centralWidget);

    // Liitytään servulle
    socket.connectToHost("localhost", 12345);
    connect(&socket, &QTcpSocket::readyRead, this, [this]() { receiveMessage(); });
}

void ChatWindow::receiveMessage(QString message)
{
    chatDisplay->append("Other Window: " + message);
}

void ChatWindow::sendMessage()
{
    QString message = inputField->text();
    if (!message.isEmpty())
    {
        if (socket.state() == QAbstractSocket::ConnectedState) {
            socket.write(message.toUtf8() + "\n");
            socket.flush();
            inputField->clear();

            chatDisplay->append("You: " + message);

            // Emitoidaan signaali ikkunalta ikkunalle
            emit sendMessageToWindow(message);
        } else {
            // Hallinoidaan milloin socketti ei ole yhdistänyt
            chatDisplay->append("Error: Not connected to the server");
        }
    }
}
void ChatWindow::receiveMessage()
{
    while (socket.bytesAvailable()) {
        QByteArray data = socket.readLine();
        if (!data.isEmpty()) {
            QString message = QString::fromUtf8(data).trimmed();
            chatDisplay->append("Server: " + message);
        }
    }
}

void ChatWindow::sendMessageToOtherWindow(QString message)
{
    emit sendMessageToWindow(message);
}
void ChatWindow::disconnectFromServer()
{
    socket.disconnectFromHost();
    socket.waitForDisconnected();
}

ChatWindow::~ChatWindow()
{
    // siivotaan jääneet prosessit ja muut resurssit
    socket.disconnectFromHost();
    socket.waitForDisconnected();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //servu instance päälle
    ChatServer server;

    // tarkastetaan serveriltä ongelmia
    if (!server.listen(QHostAddress::Any, 12345)) {
        qDebug() << "Failed to start the server. Error:" << server.errorString();
        return 1;
    }
    qDebug() << "Server started. Listening on port" << server.serverPort();


    ChatWindow window1;
    ChatWindow window2;


    QObject::connect(&window1, SIGNAL(sendMessageToWindow(QString)), &window2, SLOT(receiveMessage(QString)));
    QObject::connect(&window2, SIGNAL(sendMessageToWindow(QString)), &window1, SLOT(receiveMessage(QString)));


    // Poistetaan ikkunat servulta kun ne suljetaan.
    QObject::connect(&window1, &ChatWindow::destroyed, &window1, &ChatWindow::disconnectFromServer);
    QObject::connect(&window2, &ChatWindow::destroyed, &window2, &ChatWindow::disconnectFromServer);

    window1.show();
    window2.show();

    return app.exec();
}
