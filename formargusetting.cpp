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
