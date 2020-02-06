#ifndef FORMCALIBRATIONTEST_H
#define FORMCALIBRATIONTEST_H

#include <QWidget>
#include "globalvariable.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

namespace Ui {
class FormCalibrationTest;
}

class FormCalibrationTest : public QWidget
{
    Q_OBJECT

public:
    explicit FormCalibrationTest(QWidget *parent = 0);
    ~FormCalibrationTest();

    void loadPara();
    void savePara();
    void updateForm();
private slots:
    void on_pushButton_reset_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FormCalibrationTest *ui;
};

#endif // FORMCALIBRATIONTEST_H
