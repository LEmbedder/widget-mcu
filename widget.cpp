#include "widget.h"
#include "ui_widget.h"
#include "navprogress.h"
#include "progressbar.h"
#include "formmain.h"
#include "globalvariable.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    /**
     * 设置没有鼠标箭头
    */
//    QWidget::setCursor(QCursor(Qt::BlankCursor));
    /* 更行时钟的时间显示 */
    timer  = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerOut()));
    timer->start(500);
    /*
     * 显示进度条
    */
//    pb = new ProgressBar(ui->widget_6);
//    pb->setFixedSize(700,50);
//    pb->setProgressValue(2.6);
    fp = new FormProgress();
    ui->widget_6->layout()->addWidget(fp);
    fp->setFixedSize(700,30);


    /*
     * 初始化变量
     */
    communication = new communicationToMCU;

    /*
     * 添加控制主界面显示
    */
    formain = new FormMain(this);
    formain->formProgress = fp;
    formain->communication = communication;
    connect(communication,SIGNAL(update_label(bool)),formain,SLOT(updateLabelSucessOrFailed(bool)));
    connect(communication,SIGNAL(update_channel()),formain,SLOT(channel_update_start_timer()));
    communication->serialPort = formain->serialPort;
//    connect(communication->serialPort,SIGNAL(readyRead()),formain,SLOT(receiveInfo()));
    formain->setViewData();
    ui->verticalLayout_target->addWidget(formain);
    communication->DataInit(0xaa,0x00);
    communication->start_first();
    /* 更行界面 */
    updateForm();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateForm()
{
    /* 显示版本号 */
    ui->version->setText(VERSION);
    /* 初始化其他显示 */
    fp->setProgressValue(process);

}

void Widget::timerOut()
{
    current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy/MM/dd--hh:mm:ss ddd");
    ui->label_time->setText(current_date);
//    QTimeZone timeZone;
//    timeZone.
//    qDebug()<< timeZone.offsetFromUtc(current_date_time);
//    qDebug()<<timeZone.id();
}

/*
 * 数据库练习使用
*/
void Widget::testSql()
{
    /* 参考支持的数据库:QSQLITE */
//    QStringList drivvers = QSqlDatabase::drivers();
//    foreach (QString driver, drivvers) {
//        qDebug()<<driver;
//    }
//    db.close();
//    db.removeDatabase("QSQLITE");

}
