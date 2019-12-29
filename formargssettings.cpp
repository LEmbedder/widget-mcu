#include "formargssettings.h"
#include "ui_formargssettings.h"

FormArgsSettings::FormArgsSettings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::FormArgsSettings)
{
    ui->setupUi(this);
//    QWidget::setCursor(QCursor(Qt::BlankCursor));
    setFixedSize(800,480);
}

FormArgsSettings::~FormArgsSettings()
{
    delete ui;
}

void FormArgsSettings::on_pushButton_5_clicked()
{
    close();
    emit emitClicked(true);
}

void FormArgsSettings::on_pushButton_4_clicked()
{

}
