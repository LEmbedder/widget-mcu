#include "formmain.h"
#include "ui_formmain.h"
#include <QDebug>

FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);
    ui->pushButton->setChecked(true);

    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formChannleSettings = new FormChannelSettings;
    ui->verticalLayout_2->addWidget(formChannleSettings);
    formChannleSettings->close();

    formArguSetting = new FormArguSetting;
    ui->verticalLayout_2->addWidget(formArguSetting);
    formArguSetting->close();

    formViewData = new FormViewData;
    ui->verticalLayout_2->addWidget(formViewData);
    formViewData->close();


}

FormMain::~FormMain()
{
    delete ui;
}

void FormMain::on_pushButton_clicked()
{
    qDebug()<<"on_pushButton_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formChannleSettings->close();
    formArguSetting->close();
    formViewData->close();
    ui->widget_target->show();

}

void FormMain::on_pushButton_2_clicked()
{
    qDebug()<<"on_pushButton_2_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formChannleSettings->close();
    ui->widget_target->close();
    formViewData->close();
    formArguSetting->show();
}

void FormMain::on_pushButton_3_clicked()
{
    qDebug()<<"on_pushButton_3_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formArguSetting->close();
    ui->widget_target->close();
    formChannleSettings->close();
    formViewData->show();
}

void FormMain::on_pushButton_4_clicked()
{
    qDebug()<<"on_pushButton_4_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formArguSetting->close();
    ui->widget_target->close();
    formViewData->close();
    formChannleSettings->show();
}
void FormMain::witchButtonChecked(QPushButton *button)
{
    if(button->isChecked())
    {
        button->setStyleSheet("background-color: rgb(196, 160, 0);");
    }
    else
    {
        button->setStyleSheet("background-color: rgb(200, 200, 200);");
    }
}
