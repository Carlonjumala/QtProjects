#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>


class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    void setDate(QPainter*, int, int);
    void setOffset(int newOffset);
    int getOffset() const;

    void setDateOffset(int newDateOffset);
    int getDateOffset() const;

signals:

protected:
    void paintEvent(QPaintEvent*event)override;

private:
    QDate *date;
    QTime *tempTime;


    int offset =0;
    int dateOffset =0;
};

#endif // WIDGET_H
