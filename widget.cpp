#include "widget.h"
#include "ui_widget.h"
#include "navprogress.h"
#include "progressbar.h"
#include "formmain.h"
#include "formchannelsettings.h"
#include "formchannlesettings2.h"
#include "formargssettings.h"
#include "formchannelsettings.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    QWidget::setCursor(QCursor(Qt::BlankCursor));

    timer  = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerOut()));
    timer->start(500);
//    NavProgress *np = new NavProgress(this);
//    np->setFixedSize(800,50);
//    pb = new ProgressBar(this);
//    pb->setFixedSize(800,100);
//    pb->setProgressValue(0);

    FormMain *formain = new FormMain(this);
    ui->verticalLayout_target->addWidget(formain);
//    FormChannelSettings *fcs = new FormChannelSettings(this);
//    FormChannelSettings *fcs2 = new FormChannelSettings(this);

}

Widget::~Widget()
{
    delete ui;
}
void Widget::timerOut()
{
    current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy/MM/dd--hh:mm:ss ddd");
    ui->label_time->setText(current_date);
}
