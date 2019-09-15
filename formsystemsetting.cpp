#include "formsystemsetting.h"
#include "ui_formsystemsetting.h"

FormSystemSetting::FormSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSystemSetting)
{
    ui->setupUi(this);
}

FormSystemSetting::~FormSystemSetting()
{
    delete ui;
}

void FormSystemSetting::on_pushButton_return_clicked()
{
    this->close();
}
