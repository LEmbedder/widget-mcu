#ifndef FORMARGUSETTING_H
#define FORMARGUSETTING_H

#include <QWidget>
#include <formsystemsetting.h>
#include <formtimesetting.h>
#include <formpasswordsetting.h>
#include "formcalibration.h"
#include "formextend.h"
#include "formpassword.h"

namespace Ui {
class FormArguSetting;
}

class FormArguSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormArguSetting(QWidget *parent = 0);
    ~FormArguSetting();
    FormSystemSetting *formSystemSetting;
    FormTimeSetting *formTimeSetting;
    FormPasswordSetting *formPasswordSetting;
    FormCalibration *formCalibration;
    FormExtend *formExtend;
    FormPassword *fps;
    struct Args_config args_config;
private slots:
    void on_pushButton_systemSetting_clicked();

    void on_pushButton_timeSetting_clicked();

    void on_pushButton_passWord_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void slots_save_args_config(struct Args_config *config);

private:
    Ui::FormArguSetting *ui;

};

#endif // FORMARGUSETTING_H
