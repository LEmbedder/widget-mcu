#include "formviewdata.h"
#include "ui_formviewdata.h"

FormViewData::FormViewData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormViewData)
{
    ui->setupUi(this);
}

FormViewData::~FormViewData()
{
    delete ui;
}
