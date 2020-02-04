#include "formextend.h"
#include "ui_formextend.h"

FormExtend::FormExtend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormExtend)
{
    ui->setupUi(this);
}

FormExtend::~FormExtend()
{
    delete ui;
}

void FormExtend::on_pushButton_2_clicked()
{
    close();
}

void FormExtend::on_pushButton_ts_calibrate_clicked()
{
    system("ts_calibrate");
    update();
}
