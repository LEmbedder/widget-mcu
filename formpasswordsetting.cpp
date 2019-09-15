#include "formpasswordsetting.h"
#include "ui_formpasswordsetting.h"

FormPasswordSetting::FormPasswordSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPasswordSetting)
{
    ui->setupUi(this);
}

FormPasswordSetting::~FormPasswordSetting()
{
    delete ui;
}

void FormPasswordSetting::on_pushButton_return_clicked()
{
    close();
}
