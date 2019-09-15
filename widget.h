#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QTimer>
#include "progressbar.h"
#include <QDateTime>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QTimer *timer;
private slots:
    void timerOut();
private:
    Ui::Widget *ui;
    QDateTime current_date_time;
    QString current_date;
    double value;

    ProgressBar *pb;
};

#endif // WIDGET_H
