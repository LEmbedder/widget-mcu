#include "formtimesetting.h"
#include "ui_formtimesetting.h"

FormTimeSetting::FormTimeSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTimeSetting)
{
    ui->setupUi(this);
    ui->lineEdit_yy->setPlaceholderText("yyyy");
    ui->lineEdit_yy->setMaxLength(4);
    QRegExp regExp("^[1-2]*[0-9][0-9]*$");//创建了一个模式
//    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);//创建了一个表达式
    ui->lineEdit_yy->setValidator(new QRegExpValidator(regExp, this));//交付使用

    ui->lineEdit_mm->setMaxLength(2);
    ui->lineEdit_mm->setPlaceholderText("mm");
    ui->lineEdit_mm->setValidator(new QRegExpValidator(QRegExp("(([0-9]([0-9]{1})|(1[1|2]))| ([2-9]{1}))"), this));
    ui->lineEdit_dd->setMaxLength(2);
    ui->lineEdit_dd->setPlaceholderText("dd");
    ui->lineEdit_dd->setValidator(new QRegExpValidator(QRegExp("(([0-2]([1-9]{1}))|(3[0|1]))"), this));

    ui->lineEdit_hh->setMaxLength(2);
    ui->lineEdit_hh->setPlaceholderText("hh");
    ui->lineEdit_hh->setValidator(new QRegExpValidator(QRegExp("(([0-1]([1-9]{1}))|(2[0-3]))"), this));
    ui->lineEdit_mi->setMaxLength(2);
    ui->lineEdit_mi->setPlaceholderText("mm");
    ui->lineEdit_mi->setValidator(new QRegExpValidator(QRegExp("([0-5][0-9])"), this));
    ui->lineEdit_ss->setMaxLength(2);
    ui->lineEdit_ss->setPlaceholderText("ss");
    ui->lineEdit_ss->setValidator(new QRegExpValidator(QRegExp("([0-5][0-9])"), this));
}

FormTimeSetting::~FormTimeSetting()
{
    delete ui;
}

void FormTimeSetting::on_pushButton_return_clicked()
{
    close();
}
/*
 * 设置时间
 */
void FormTimeSetting::on_pushButton_setted_clicked()
{
    timeString = ui->lineEdit_yy->text()+"."+ui->lineEdit_mm->text()+"."+ui->lineEdit_dd->text()+"-"+
            ui->lineEdit_hh->text()+":"+ui->lineEdit_mi->text()+":00";
    timeString  = "date -s"+timeString;
    system(timeString.toStdString().c_str());
    system("hwclock -w");
}
