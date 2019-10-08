#include "widget.h"
#include "ui_widget.h"
#include "navprogress.h"
#include "progressbar.h"
#include "formmain.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    QWidget::setCursor(QCursor(Qt::BlankCursor));
    //更行时间显示
    timer  = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerOut()));
    timer->start(500);
//    NavProgress *np = new NavProgress(ui->widget_6);
//    np->setFixedSize(800,50);
    pb = new ProgressBar(ui->widget_6);
    pb->setFixedSize(700,50);
    pb->setProgressValue(2.6);

    FormMain *formain = new FormMain(this);
    ui->verticalLayout_target->addWidget(formain);

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
