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

    QSqlTableModel *model;
    QTableView *view;
    bool initDatabase();
    void insertDatabase(QString worker_number,
                        QString workpiece_number,
                        QString test_time,
                        int revealStandardUpLimit,
                        int revealStandardDownLimit,
                        QString temp_test_result_unit,
                        QString result,
                        QString test_press_unit,
                        int meter_number);
private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_top_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_bottom_clicked();

private:
    Ui::FormViewData *ui;
    void page_value();
    unsigned total_number;
    unsigned pass;
    double percent_pass;

    void update_args();
};

#endif // FORMVIEWDATA_H
