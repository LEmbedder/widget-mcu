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

    QSqlQueryModel *model;
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
private:
    Ui::FormViewData *ui;
};

#endif // FORMVIEWDATA_H
