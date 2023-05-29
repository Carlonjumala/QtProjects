#include "widget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QPen>
#include <QtMath>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    // Ajastin.
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Widget::update));
    timer->start(1000); // Alustetaan ajastin sekunnin välillä

    date = new QDate;
    tempTime = new QTime;

    setWindowTitle(tr("Analog Clock"));
    resize(800, 800); // Alustetaan alkuperäinen koko
}

void Widget::paintEvent(QPaintEvent *)
{
    // Definataan koordinaatit tunti minuutti ja sekka viisareille
    static const QPoint hourHand[4] = {
        QPoint(-2, -60),
        QPoint(2, -60),
        QPoint(2, 0),
        QPoint(-2, 0)
    };

    static const QPoint minuteHand[4] = {
        QPoint(-2, -100),
        QPoint(2, -100),
        QPoint(2, 0),
        QPoint(-2, 0)
    };

    static const QPoint secondHand[4] = {
        QPoint(-2, -120),
        QPoint(2, -120),
        QPoint(2, 8),
        QPoint(-2, 8)
    };

    QColor hourColor(250, 250, 250);
    QColor minuteColor(250, 250, 250);
    QColor secondColor(127, 0, 0);
    QColor backgroundColor(0, 0, 0);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime().addSecs(offset);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 400.0, side / 400.0);

    // Draw the background
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor);
    painter.drawEllipse(QRectF(-145, -145, 290, 290));

    // Draw the hour hand
    painter.setPen(hourColor);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(30.0 * (time.hour() % 12 + time.minute() / 60.0));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();

    // Draw the minute hand
    painter.setPen(minuteColor);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();

    // Draw the second hand
    painter.setPen(secondColor);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 4);
    painter.restore();

    QColor dateColor(255, 255, 255);

    painter.setPen(dateColor);
    QDateTime datetime = QDateTime::currentDateTime().addDays(dateOffset);
    setDate(&painter, datetime.date().day(), datetime.date().month());
}

void Widget::setDate(QPainter *painter, int day, int month)
{
    // Määritetään päiovä
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    QString dateString;
    if (day < 10 && month < 10){
        dateString = QString("0%1.0%2").arg(QString::number(day), QString::number(month));
    }else if(month < 10){
        dateString = QString("%1.0%2").arg(QString::number(day), QString::number(month));
    }else if (day < 10){
        dateString = QString("0%1.%2").arg(QString::number(day), QString::number(month));
    }else{
        dateString = QString("%1.%2").arg(QString::number(day), QString::number(month));
    }
    //Piirretään dataString painteria hyödyksi käyttäen
}

void Widget::setOffset(int newOffset){
    offset = newOffset;
}

int Widget::getOffset() const
{
    return offset;
}

void Widget::setDateOffset(int newDateOffset){
    dateOffset = newDateOffset;
}

int Widget::getDateOffset()const{
    return dateOffset;
}
