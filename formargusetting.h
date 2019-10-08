#ifndef FORMARGUSETTING_H
#define FORMARGUSETTING_H

#include <QWidget>
#include <formsystemsetting.h>
#include <formtimesetting.h>
#include <formpasswordsetting.h>
#include "formcalibration.h"
#include "formextend.h"

namespace Ui {
class FormArguSetting;
}

class FormArguSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormArguSetting(QWidget *parent = 0);
    ~FormArguSetting();

private slots:
    void on_pushButton_systemSetting_clicked();

    void on_pushButton_timeSetting_clicked();

    void on_pushButton_passWord_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::FormArguSetting *ui;
    FormSystemSetting *formSystemSetting;
    FormTimeSetting *formTimeSetting;
    FormPasswordSetting *formPasswordSetting;
    FormCalibration *formCalibration;
    FormExtend *formExtend;
};

#endif // FORMARGUSETTING_H
