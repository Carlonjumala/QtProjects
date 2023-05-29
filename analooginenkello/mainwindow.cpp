#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QDate>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->timeEdit();
    clock=ui->widget;
}

MainWindow::~MainWindow(){delete ui;}



void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    QTime currentTime = QTime::currentTime();
    int seconds = currentTime.secsTo(time);
    clock->setOffset(seconds);
    clock->update();
}

void MainWindow::on_timeButton_clicked(QWidget *parent)
{

    int hour = ui->timeEdit->time().hour();
    qInfo()<<hour;

    int minute = ui->timeEdit->time().minute();
    qInfo()<<minute;

    int second = ui->timeEdit->time().second();
    qInfo()<<second;

    QTime tempTime;

    tempTime.setHMS(hour, minute, second, QTime::currentTime().msec());
    qInfo()<<tempTime;

    clock->setOffset(QTime::currentTime().secsTo(tempTime));
    qInfo()<<clock->getOffset();

}


void MainWindow::on_timeButton_2_clicked(QWidget*parent)
{
    clock->setOffset(0);
}

void MainWindow::on_dateTimeEdit_dateChanged(const QDate &date)
{

}

void MainWindow::on_pushButton_clicked(QWidget*parent)
{
    int day = ui->dateTimeEdit->date().day();
    qInfo()<<day;

    int month = ui->dateTimeEdit->date().month();
    qInfo()<<month;

    int year = ui->dateTimeEdit->date().year();
    qInfo()<<year;

    QDate date;
    date.setDate(year,month,day);
    clock->setDateOffset(QDate::currentDate().daysTo(date));
    qInfo()<<clock->getDateOffset();
}

void MainWindow::on_pushButton_2_clicked()
{
    clock->setDateOffset(0);
}
