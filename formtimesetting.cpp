#include "formtimesetting.h"
#include "ui_formtimesetting.h"

FormTimeSetting::FormTimeSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTimeSetting)
{
    ui->setupUi(this);
}

FormTimeSetting::~FormTimeSetting()
{
    delete ui;
}

void FormTimeSetting::on_pushButton_return_clicked()
{
    close();
}
