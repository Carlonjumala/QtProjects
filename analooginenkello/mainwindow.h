#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "widget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_timeButton_clicked(QWidget *parent=nullptr);



    void on_timeButton_2_clicked(QWidget*parent = nullptr);

    void on_dateTimeEdit_dateChanged(const QDate &date);

    void on_pushButton_clicked(QWidget*parent = nullptr);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Widget *clock=nullptr;

};
#endif // MAINWINDOW_H
