#include "formviewdata.h"
#include "ui_formviewdata.h"
#include <QAbstractItemView>
#include <QScrollBar>
#include <QSqlRecord>
#include <QFileDialog>
#include <QHeaderView>

FormViewData::FormViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormViewData)
{
    ui->setupUi(this);
    memset(&data_view_all, 0 ,sizeof(struct statistic_args));

    viewFPS = new FormPassword;
    connect(viewFPS,SIGNAL(emitIsTrue_2()),this,SLOT(on_pushButton_clicked()));
    connect(viewFPS,SIGNAL(emitIsTrue_3()),this,SLOT(on_pushButton_2_clicked()));
    connect(viewFPS,SIGNAL(emitIsTrue_4()),this,SLOT(on_pushButton_3_clicked()));
    initDatabase();
    page_value();
    update_args();
//    insertDatabase("127","1451122","2020-19-19","1651pa","684pa","1353pa","true","1234kpa","13s");

}

FormViewData::~FormViewData()
{
    delete ui;
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
    else
    {
    }
    QSqlQuery query;
    query.exec("create table testdata("
               "id int primary key, "
               "worker_number varchar ,"
               "workpiece_number varchar,"
               "test_time varchar,"
               "revealStandardUpLimit varchar,"
               "revealStandardDownLimit varchar,"
               "temp_test_result_unit varchar,"
               "result varchar,"
               "test_press_unit varchar,"
               "meter_number varchar)"
               );

    model = new QSqlTableModel(this);
    model->setTable("testdata");
    model->select();
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
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->widget_5->layout()->addWidget(view);
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
                                  QString revealStandardUpLimit,
                                  QString revealStandardDownLimit,
                                  QString temp_test_result_unit,
                                  QString result,
                                  QString test_press_unit,
                                  QString meter_number)
{
    int next = 1;
    QSqlQuery query = QSqlQuery(db);

    bool buscess = query.exec("select * from testdata");
    if(false == buscess)
    {
        printf("select from testdata failed\n");
    }
    if (query.last())
    {
        next = query.at() + 2;
        if (next > MAX_DB_RECORD)
        {
            printf("data base is full,can't store");
            return;
        }
    }


   buscess = query.exec("insert into testdata values("+
                   QString::number(next)+",'"+
                   worker_number+"','"+
                   workpiece_number+"','"+
                   test_time+"','"+
                   revealStandardUpLimit+"','"+
                   revealStandardDownLimit+"','"+
                   temp_test_result_unit+"','"+
                   result+"','"+
                   test_press_unit+"','"+
                   meter_number+"')");


    if(false == buscess)
    {
        printf("insert into testdata failed!\n");
    }
    model->select();
    view->viewport()->update();
    update_args();
}

/*
 *  search data
 */
void FormViewData::on_pushButton_search_clicked()
{
    int mode = 0;
    QString date;
    QString worker_number = ui->lineEdit_worker_number->text().trimmed();
    QString workpiece_number = ui->lineEdit_workpiece_number->text().trimmed();

    if (ui->checkBox_date->isChecked()
            && !ui->lineEdit_yy->text().trimmed().isEmpty()
            && !ui->lineEdit_mm->text().trimmed().isEmpty()
            && !ui->lineEdit_dd->text().trimmed().isEmpty())
    {
        mode |= 1 << 0;
        date = ui->lineEdit_yy->text().trimmed()+"-"+
               ui->lineEdit_mm->text().trimmed()+"-"+
               ui->lineEdit_dd->text().trimmed();
    }
    if (ui->checkBox_worker_number->isChecked()
            && !worker_number.isEmpty())
    {
        mode |= 1 << 1;
    }
    if (ui->checkBox_workpiece_number->isChecked()
            && !workpiece_number.isEmpty())
    {
        mode |= 1 << 2;
    }
    switch (mode)
    {
    case 0x00:
        model->setFilter("");
        break;
    case 0x01:
        model->setFilter(QString("test_time = '%1'").arg(date));
        break;
    case 0x02:
        model->setFilter(QString("worker_number = '%1'").arg(worker_number));
        break;
    case 0x03:
        model->setFilter(QString("(test_time = '%1') AND (worker_number = '%2')").arg(date).arg(worker_number));
        break;
    case 0x04:
        model->setFilter(QString("workpiece_number = '%1'").arg(workpiece_number));
        break;
    case 0x05:
        model->setFilter(QString("(test_time = '%1') AND (workpiece_number = '%2')").arg(date).arg(workpiece_number));
        break;
    case 0x06:
        model->setFilter(QString("(worker_number = '%1') AND (workpiece_number = '%2')").arg(worker_number).arg(workpiece_number));
        break;
    case 0x07:
        model->setFilter(QString("(test_time = '%1') AND (worker_number = '%2') AND (workpiece_number = '%3')")
                         .arg(date).arg(worker_number).arg(workpiece_number));
        break;
    default:
        model->setFilter("");
        break;
    }
    qDebug()<<model->filter();
    model->select();
    update_statistics_args();
    page_value();
}
/*
 *  统计测试结果
 */
void FormViewData::update_statistics_args()
{
    QString result = "";

    memset(&data_view_select, 0 ,sizeof(struct statistic_args));

    if (model != NULL)
    {
        data_view_select.total_number = model->rowCount();
        for (unsigned i = 0; i < data_view_select.total_number; i++)
        {
            /*  */
            result = model->data(model->index(i, 6)).toString();
            if (result == BIT_LEAK)
            {
                data_view_select.big_leak++;
            }
            else if (result == ADD_NG_NUMBER)
            {
                data_view_select.add_NG_nubmer++;
            }
            else if (result == LOSE_NG_NUMBER)
            {
                data_view_select.lose_NG_number++;
            }
            else if (result == UP_RANGE_UPPERLIMIT_NUMBER)
            {
                data_view_select.up_range_upperlimit_number++;
            }
            else if (result == DOWN_RANGE_DOWNERLIMIT_NUMBER)
            {
                data_view_select.down_range_downerlimit_number++;
            }
            else if (result == TEST_PRESS_DOWNERLIMIT_NUMBER)
            {
                data_view_select.test_press_upperlimit_number++;
            }
            else if (result == TEST_PRESS_DOWNERLIMIT_NUMBER)
            {
                data_view_select.test_press_upperlimit_number++;
            }
            else if (result == PASS){
                data_view_select.pass++;
            }
            else{
                DEBUG_LOG("store data error\n");
            }
        }/* end for */
        update_statistics_view(data_view_select);

    }

}
void FormViewData::update_statistics_view(struct statistic_args args)
{
    /* 在界面显示 */
    ui->label_total->setText(QString::number(args.total_number));
    ui->label_pass->setText(QString::number(args.pass));
    ui->label_big_leak->setText(QString::number(args.big_leak));
    ui->label_add_NG->setText(QString::number(args.add_NG_nubmer));
    ui->label_lose_NG->setText(QString::number(args.lose_NG_number));
    ui->label_up_range_upperlimit_number->setText(QString::number(args.up_range_upperlimit_number));
    ui->label_down_range_downerlimit_number->setText(QString::number(args.down_range_downerlimit_number));
    ui->label_test_press_upperlimit_number->setText(QString::number(args.test_press_upperlimit_number));
    ui->label_test_press_downerlimit_number->setText(QString::number(args.test_press_downerlimit_number));
    if (args.total_number != 0)
    {
        args.percent_pass = args.pass*100.0/args.total_number;
        ui->label_percent_pass->setText(QString::number(args.percent_pass,'f',2)+"%");
    }
    else
    {
        args.percent_pass = 0;
        ui->label_percent_pass->setText(QString::number(args.percent_pass,'f',2)+"%");
    }
}
void FormViewData::on_pushButton_top_clicked()
{
    view->verticalScrollBar()->setSliderPosition(0);
    page_value();
    page_value();
}

void FormViewData::on_pushButton_up_clicked()
{
    int position = view->verticalScrollBar()->value();
    int page_step = view->verticalScrollBar()->pageStep();

    position -= page_step;
    if (position < 0)
    {
        position = 0;
    }
    view->verticalScrollBar()->setSliderPosition(position);
    page_value();
}

void FormViewData::on_pushButton_down_clicked()
{
    int position = view->verticalScrollBar()->value();
    int page_step = view->verticalScrollBar()->pageStep();

    position += page_step;
    if (position > view->verticalScrollBar()->maximum())
    {
        position = view->verticalScrollBar()->maximum();
    }
    view->verticalScrollBar()->setSliderPosition(position);
    page_value();
}

void FormViewData::on_pushButton_bottom_clicked()
{
    int position = view->verticalScrollBar()->maximum();

    view->verticalScrollBar()->setSliderPosition(position);
    page_value();
}

void FormViewData::page_value()
{
    int value = view->verticalScrollBar()->value()+1;
    int max_page = model->rowCount()-6;

    if (max_page <= 0)
    {
        max_page = 1;
    }
    if (value > max_page) value = max_page;
    ui->label_value->setText(QString::number(value)+"/"+
                             QString::number(max_page));
    update();
}


/*
 * 更新的是全部的内容数据
 */
void FormViewData::update_args()
{
    QString result = "";

    if (model != NULL)
    {
        data_view_all.total_number = model->rowCount();
        for (unsigned i = 0; i < data_view_all.total_number; i++)
        {
            /*  */
            result = model->data(model->index(i, 6)).toString();
            if (result == BIT_LEAK)
            {
                data_view_all.big_leak++;
            }
            else if (result == ADD_NG_NUMBER)
            {
                data_view_all.add_NG_nubmer++;
            }
            else if (result == LOSE_NG_NUMBER)
            {
                data_view_all.lose_NG_number++;
            }
            else if (result == UP_RANGE_UPPERLIMIT_NUMBER)
            {
                data_view_all.up_range_upperlimit_number++;
            }
            else if (result == DOWN_RANGE_DOWNERLIMIT_NUMBER)
            {
                data_view_all.down_range_downerlimit_number++;
            }
            else if (result == TEST_PRESS_DOWNERLIMIT_NUMBER)
            {
                data_view_all.test_press_upperlimit_number++;
            }
            else if (result == TEST_PRESS_DOWNERLIMIT_NUMBER)
            {
                data_view_all.test_press_upperlimit_number++;
            }
            else if (result == PASS){
                data_view_all.pass++;
            }
            else{
                DEBUG_LOG("store data error\n");
            }
        }/* end for */
    }
    update_statistics_view(data_view_all);
}

/*
 * 打印选择信息
 *  QString worker_number,
    QString workpiece_number,
    QString test_time,
    int revealStandardUpLimit,
    int revealStandardDownLimit,
    QString temp_test_result_unit,
    QString result,
    QString test_press_unit,
    int meter_number)
 */
void FormViewData::on_pushButton_print_clicked()
{
    int row;
    Print print;

    row = view->currentIndex().row();
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("select * from testdata");
    query->seek(row);
    QSqlRecord record = query->record();
    print.workpiece_number = record.value("workpiece_number").toString();
    print.worker_number = record.value("worker_number").toString();
    print.device_number = QString(systemData.args_config.device_number);
    print.result = record.value("result").toString()+"("+record.value("test_press_unit").toString()+")";
    print.timer = record.value("test_time").toString();
    qDebug()<<print.workpiece_number<<print.worker_number<<print.result<<print.timer;

    printInformation->print(&print);
}
/*
 * 导出数据库信息为csv文件
 */
void FormViewData::ReadDataFromSqlWriteToCSV(const QString &tableName,const QString &csvFileName)
{
    QStringList strList;
    QString strString;
    const QString FILE_PATH(csvFileName);
    QFile csvFile(FILE_PATH);

    model->setTable(tableName);
    model->select();
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
    if (csvFile.open(QIODevice::ReadWrite))
    {
        for (int i=0;i<model->rowCount();i++)
        {
            for(int j=0; j < model->columnCount();j++)
            {
                strList.insert(j,model->data(model->index(i,j)).toString());//把每一行的每一列数据读取到strList中
            }
            strString = strList.join(", ")+"\n";//给两个列数据之前加“,”号，一行数据末尾加回车
            strList.clear();//记录一行数据后清空，再记下一行数据
            csvFile.write(strString.toUtf8());//使用方法：转换为Utf8格式后在windows下的excel打开是乱码,可先用notepad++打开并转码为unicode，再次用excel打开即可。
        }
        csvFile.close();
    }
    if (!system("ls /mnt/usb > /dev/null"))
    {
        if (!system("cp /testdata.csv /mnt/usb"))
        {
            system("sync");
            /* 说明拷贝完成 */
            dial.showMessage(2000,"拷贝完成");
            system("umount /mnt/usb");

        }else{
            dial.showMessage(2000,"拷贝失败");

        }

    }
    else
        dial.showMessage(2000,"请插入存储设备");
}

void FormViewData::on_pushButton_clicked()
{
    if (viewFPS->isTrue != true)
    {
        viewFPS->show();
        viewFPS->type = 1;
    }
    viewFPS->clearText();
    qDebug()<<viewFPS->isTrue<<viewFPS->type;
    if (viewFPS->isTrue == true && viewFPS->type == 1)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            /* 复制数据 */
            ReadDataFromSqlWriteToCSV("testdata","testdata.csv");
        }
    }
    viewFPS->isTrue = false;
}

void FormViewData::on_pushButton_2_clicked()
{
    if (viewFPS->isTrue != true)
    {
        viewFPS->show();
        viewFPS->type = 2;
    }
    viewFPS->clearText();
    qDebug()<<viewFPS->isTrue<<viewFPS->type;
    if (viewFPS->isTrue == true && viewFPS->type == 2)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            model->setFilter("");
            /* 在这里添加删除数据库内容 */
            while(model->rowCount()){

                model->select();
                unsigned total_number = model->rowCount();
                qDebug()<<"remove total_number: "<<total_number;
//                for (unsigned i = 0; i < total_number; i++)
//                {
                    model->removeRows(0,total_number);
//                }
                model->submitAll();
            }
            model->select();
            update_args();
        }
    }
    viewFPS->isTrue = false;
}

/* 选择使用哪种数据显示 */
void FormViewData::on_pushButton_total_clicked()
{
    update_statistics_view(data_view_all);
}

void FormViewData::on_pushButton_select_clicked()
{
    update_statistics_view(data_view_select);
}

void FormViewData::on_pushButton_3_clicked()
{
    if (viewFPS->isTrue != true)
    {
        viewFPS->show();
        viewFPS->type = 3;
    }
    viewFPS->clearText();
    qDebug()<<viewFPS->isTrue<<viewFPS->type;
    if (viewFPS->isTrue == true && viewFPS->type == 3)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            /* 在这里添加删除数据库内容 */
            on_pushButton_search_clicked();
            unsigned total_number = model->rowCount();
            qDebug()<<"remove select_number: "<<total_number;
            for (unsigned i = 0; i < total_number; i++)
            {
                model->removeRow(i);
            }
            model->submitAll();
        }
    }
    viewFPS->isTrue = false;
}
