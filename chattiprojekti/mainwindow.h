#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QToolbar>
#include <QLabel>


class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    void disconnectFromServer(); // Added declaration
    void sendMessage();

public slots:
    void receiveMessage(QString message);

    void sendMessageToOtherWindow(QString message);

private slots:
    void receiveMessage();



signals:
    void messageReceived(QString message);
    void sendMessageToWindow(QString message);




private:
    QTextEdit *chatDisplay;
    QLineEdit *inputField;
    QTcpSocket socket;
    QToolBar *toolbar;

};

#endif // MAINWINDOW_H
