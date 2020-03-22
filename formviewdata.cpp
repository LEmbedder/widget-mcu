#include "formviewdata.h"
#include "ui_formviewdata.h"

FormViewData::FormViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormViewData)
{
    ui->setupUi(this);

    initDatabase();
//    insertDatabase("127","1451122","2020-19-19",1651,684,"1353pa","true","1234kpa",13);
    model = new QSqlQueryModel(this);
    model->setQuery("select * from testdata");
    model->setHeaderData(0,Qt::Horizontal,tr("序号"));
    model->setHeaderData(1,Qt::Horizontal,tr("工号"));
    model->setHeaderData(2,Qt::Horizontal,tr("工件号"));
    model->setHeaderData(3,Qt::Horizontal,tr("测试时间"));
    model->setHeaderData(4,Qt::Horizontal,tr("泄露标准上限"));
    model->setHeaderData(5,Qt::Horizontal,tr("泄露标准下限"));
    model->setHeaderData(6,Qt::Horizontal,tr("测试漏率及单位"));
    model->setHeaderData(7,Qt::Horizontal,tr("结果"));
    model->setHeaderData(8,Qt::Horizontal,tr("测试压及单位"));
    model->setHeaderData(9,Qt::Horizontal,tr("测试节拍"));
    view = new QTableView(this);
    view->setModel(model);
    ui->widget_5->layout()->addWidget(view);

}
/*
 * 打开数据库设置名字添加数据
*/
bool FormViewData::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my.db");
    if ( !db.open() )
    {
        qDebug()<<"can't open db";
        return false;
    }
    QSqlQuery query;
    query.exec("create table testdata("
               "id int primary key, "
               "worker_number varchar ,"
               "workpiece_number varchar,"
               "test_time varchar,"
               "revealStandardUpLimit int,"
               "revealStandardDownLimit int,"
               "temp_test_result_unit varchar,"
               "result varchar,"
               "test_press_unit varchar,"
               "meter_number int)"
               );
//    query.exec("insert into testdata values(1,'123','4634615','2020-19-19',1651,684)");
//    query.exec("insert into testdata values(2,'124','19651','2020-19-19',1651,684)");
//    query.exec("insert into testdata values(3,'125','561','2020-19-19',1651,684)");
//    query.exec("insert into testdata values(4,'126','1451122','2020-19-19',1651,684)");


    return true;
}
/*
 * 直接调用此借口插入数据
 * QString worker_number,
    QString workpiece_number,
    QString test_time,
    int revealStandardUpLimit,
    int revealStandardDownLimit,
    QString temp_test_result_unit,
    QString result,
    QString test_press_unit,
    int meter_number)
 */
void FormViewData::insertDatabase(QString worker_number,
                                  QString workpiece_number,
                                  QString test_time,
                                  int revealStandardUpLimit,
                                  int revealStandardDownLimit,
                                  QString temp_test_result_unit,
                                  QString result,
                                  QString test_press_unit,
                                  int meter_number)
{
    int next;
    QSqlQuery *query = new QSqlQuery(db);

    query->exec("select * from testdata");
    if (query->last())
    {
        next = query->at() + 2;
    }
    else{
        next = 1;
    }
    query->exec("insert into testdata values("+
                QString::number(next)+",'"+
                worker_number+"','"+
                workpiece_number+"','"+
                test_time+"',"+
                QString::number(revealStandardUpLimit)+","+
                QString::number(revealStandardDownLimit)+",'"+
                temp_test_result_unit+"','"+
                result+"','"+
                test_press_unit+"',"+
                QString::number(meter_number)+")");
}
FormViewData::~FormViewData()
{
    delete ui;
}
