#include "dialogpassword.h"
#include "ui_dialogpassword.h"

DialogPassWord::DialogPassWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPassWord)
{
    ui->setupUi(this);
}

DialogPassWord::~DialogPassWord()
{
    delete ui;
}
