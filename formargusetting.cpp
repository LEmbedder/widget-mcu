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

    fps = new FormPassword;
    connect(fps,SIGNAL(emitIsTrue_2()),this,SLOT(on_pushButton_systemSetting_clicked()));
    connect(fps,SIGNAL(emitIsTrue_3()),this,SLOT(on_pushButton_timeSetting_clicked()));
    connect(fps,SIGNAL(emitIsTrue_4()),this,SLOT(on_pushButton_passWord_clicked()));
    connect(fps,SIGNAL(emitIsTrue_5()),this,SLOT(on_pushButton_12_clicked()));
    connect(fps,SIGNAL(emitIsTrue_6()),this,SLOT(on_pushButton_10_clicked()));
}

FormArguSetting::~FormArguSetting()
{
    delete ui;
}

void FormArguSetting::on_pushButton_systemSetting_clicked()
{
    fps->show();
    fps->clearText();
    fps->type = 1;
    qDebug()<<fps->type<<fps->isTrue;
    if (fps->isTrue == true && fps->type == 1)
    {
        if (passWord.sysOrUser == 1 ||passWord.sysOrUser == 2)
        {
            formSystemSetting->show();
            formSystemSetting->update_system_setting();
        }
    }
    fps->isTrue = false;
}

void FormArguSetting::on_pushButton_timeSetting_clicked()
{
    fps->show();
    fps->clearText();
    fps->type = 2;
    qDebug()<<fps->type<<fps->isTrue;
    if (fps->isTrue == true && fps->type == 2)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            formTimeSetting->show();
        }
        else{
        }
    }
    fps->isTrue = false;
}

void FormArguSetting::on_pushButton_passWord_clicked()
{
    fps->show();
    fps->clearText();
    fps->type = 3;
    qDebug()<<fps->type<<fps->isTrue;
    if (fps->isTrue == true && fps->type == 3)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 0)
        {
            formPasswordSetting->init();
            formPasswordSetting->show();
        }
        else if(passWord.sysOrUser == 2)
        {
            fps->passWordReset();
        }
    }
    fps->isTrue = false;
}

void FormArguSetting::on_pushButton_12_clicked()
{
    fps->show();
    fps->clearText();
    fps->type = 4;
    qDebug()<<fps->type<<fps->isTrue;
    if (fps->isTrue == true && fps->type == 4)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            formCalibration->show();
        }
    }
    fps->isTrue = false;
}

void FormArguSetting::on_pushButton_10_clicked()
{
    fps->show();
    fps->clearText();
    fps->type = 5;
    qDebug()<<fps->type<<fps->isTrue;
    if (fps->isTrue == true && fps->type == 5)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 2)
        {
            formExtend->show();
        }
    }
    fps->isTrue = false;
}

/* 更新界面参数 */
void FormArguSetting::slots_save_args_config(struct Args_config *config)
{
    memcpy(&args_config,config,sizeof(struct Args_config));
}
