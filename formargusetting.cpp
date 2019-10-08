#include "formargusetting.h"
#include "ui_formargusetting.h"


FormArguSetting::FormArguSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormArguSetting)
{
    ui->setupUi(this);
    formSystemSetting = new FormSystemSetting;
    formSystemSetting->close();

    formTimeSetting = new FormTimeSetting;
    formTimeSetting->close();

    formPasswordSetting = new FormPasswordSetting;
    formPasswordSetting->close();

    //calibration
    formCalibration = new FormCalibration;
    formCalibration->close();

    //extend
    formExtend = new FormExtend;
    formExtend->close();
}

FormArguSetting::~FormArguSetting()
{
    delete ui;
}

void FormArguSetting::on_pushButton_systemSetting_clicked()
{
    formSystemSetting->show();
}

void FormArguSetting::on_pushButton_timeSetting_clicked()
{
    formTimeSetting->show();
}

void FormArguSetting::on_pushButton_passWord_clicked()
{
    formPasswordSetting->show();
}

void FormArguSetting::on_pushButton_12_clicked()
{
    formCalibration->show();
}

void FormArguSetting::on_pushButton_10_clicked()
{
    formExtend->show();
}
