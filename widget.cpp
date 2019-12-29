#include "widget.h"
#include "ui_widget.h"
#include "navprogress.h"
#include "progressbar.h"
#include "formmain.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    testSql();
    QSqlQuery query;
    query.exec("select * from student");
    while( query.next() )
    {
        qDebug()<<query.value(0).toInt()<<query.value(1).toString();
    }
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
    pb = new ProgressBar(ui->widget_6);
    pb->setFixedSize(700,50);
    pb->setProgressValue(2.6);

    /*
     * 添加控制主界面显示
    */
    FormMain *formain = new FormMain(this);
    ui->verticalLayout_target->addWidget(formain);

    /*
     * 初始化变量
    */
    process  = 2.6;
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
    pb->setProgressValue(process);
}

void Widget::timerOut()
{

    current_date_time =QDateTime::currentDateTime();
    current_date =current_date_time.toString("yyyy/MM/dd--hh:mm:ss ddd");
    ui->label_time->setText(current_date);
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if ( !db.open() )
    {

    }
    QSqlQuery query;
    query.exec("create table student(id int primary key, name varchar(20))");
    query.exec("insert into student values(0,'LiMing0')");
    query.exec("insert into student values(1,'LiMing1')");
    query.exec("insert into student values(2,'LiMing2')");
    query.exec("insert into student values(3,'LiMing3')");

//    db.close();
//    db.removeDatabase("QSQLITE");

}
