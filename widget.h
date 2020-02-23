#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QTimer>
#include "progressbar.h"
#include <QDateTime>
#include <QDebug>
#include <communicationtomcu.h>
#include <QTimeZone>
#include "formmain.h"
#include "formprogress.h"

namespace Ui {
class Widget;


}

#define VERSION  "v1.1.1"


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QTimer *timer;
    FormMain *formain;
private slots:
    void updateForm();
    void timerOut();
private:
    Ui::Widget *ui;
    QDateTime current_date_time;
    QString current_date;
    double value;

//    ProgressBar *pb;
    FormProgress *fp;
    double process;
    void testSql();
};

#endif // WIDGET_H
