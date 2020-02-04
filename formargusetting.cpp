/*
 * 设置界面
 * 2020年01月26日22:07:10
*/
#include "formargusetting.h"
#include "ui_formargusetting.h"


FormArguSetting::FormArguSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormArguSetting)
{
    ui->setupUi(this);
    formSystemSetting = new FormSystemSetting;
    connect(formSystemSetting,SIGNAL(emit_update_config(Args_config*)),
            this,SLOT(slots_save_args_config(Args_config*)));
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
    formSystemSetting->loadConfigArgs();
}

FormArguSetting::~FormArguSetting()
{
    delete ui;
}

void FormArguSetting::on_pushButton_systemSetting_clicked()
{
    formSystemSetting->show();
    formSystemSetting->update_system_setting();
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

/* 更新界面参数 */
void FormArguSetting::slots_save_args_config(struct Args_config *config)
{
    memcpy(&args_config,config,sizeof(struct Args_config));
}
