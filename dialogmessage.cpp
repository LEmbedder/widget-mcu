#include "dialogmessage.h"
#include "ui_dialogmessage.h"
#include <QTimer>
#include <QColor>
#include <QPalette>
DialogMessage::DialogMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMessage)
{
    ui->setupUi(this);
    isOpen = false;
}

DialogMessage::~DialogMessage()
{
    delete ui;
}
/*
 * 弹出信息
 * time:显示时间
 * messa：提示信息
 * color：字体颜色
 */
void DialogMessage::showMessage(int timer, QString message, QColor color)
{
    if ( isOpen == false)
    {
        isOpen = true;
        QPalette pa;
        pa.setColor( QPalette::WindowText, color );
        ui->label->setPalette( pa );
        QTimer::singleShot(timer,this,SLOT(closeMessage()));
        ui->label->setText(message);
        show();
    }
}//showMessage
void DialogMessage::closeMessage()
{
    this->hide();
    this->close();
    isOpen = false;
}//coseMessage
