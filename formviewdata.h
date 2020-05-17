#ifndef FORMVIEWDATA_H
#define FORMVIEWDATA_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlError>
#include "config.h"
#include "printinformation.h"
#include "globalvariable.h"
#include "QTimer"
#include "QDateTime"
#include "dialogmessage.h"
#include "dialogpassword.h"
#include "formpassword.h"


struct statistic_args{
    unsigned total_number;
    unsigned big_leak;/* 大漏 */
    unsigned add_NG_nubmer; /* +NG */
    unsigned lose_NG_number;/* -NG */
    unsigned up_range_upperlimit_number ;/* 超量程上限 */
    unsigned down_range_downerlimit_number;/* 低量程下限 */
    unsigned test_press_upperlimit_number ;/* 测试压超上限 */
    unsigned test_press_downerlimit_number;/* 测试压低下限 */
    unsigned pass; /* 好的 */
    double percent_pass;
};

namespace Ui {
class FormViewData;
}

class FormViewData : public QWidget
{
    Q_OBJECT

public:
    explicit FormViewData(QWidget *parent = 0);
    ~FormViewData();
    QSqlDatabase db;
    PrintInformation *printInformation;
    QSqlTableModel *model;
    QTableView *view;

    bool initDatabase();
    void insertDatabase(QString worker_number,
                        QString workpiece_number,
                        QString test_time,
                        QString revealStandardUpLimit,
                        QString revealStandardDownLimit,
                        QString temp_test_result_unit,
                        QString result,
                        QString test_press_unit,
                        QString meter_number);
private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_top_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_bottom_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_total_clicked();
    void on_pushButton_select_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormViewData *ui;
    void page_value();
    struct statistic_args data_view_all, data_view_select;
    unsigned int currentTotalRecord;
    void update_args();
    DialogMessage dial;
    FormPassword *viewFPS;

    /*test use*/
    QTimer *timer;
    void ReadDataFromSqlWriteToCSV(const QString &tableName, const QString &csvFileName);
    void update_statistics_args();
    void update_statistics_view(statistic_args args);
};

#endif // FORMVIEWDATA_H
