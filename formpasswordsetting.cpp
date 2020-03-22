#include "formpasswordsetting.h"
#include "ui_formpasswordsetting.h"

FormPasswordSetting::FormPasswordSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPasswordSetting)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(15);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$"), this));
    ui->lineEdit_2->setMaxLength(15);
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$"), this));
}

FormPasswordSetting::~FormPasswordSetting()
{
    delete ui;
}
void FormPasswordSetting::init(void)
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}
void FormPasswordSetting::on_pushButton_return_clicked()
{
    close();
}

void FormPasswordSetting::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(true);
}

/*
 * 保存密码
 */
void FormPasswordSetting::on_pushButton_clicked()
{
    QString fileName = QApplication::applicationDirPath() + "/password.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("PassWord");
    if (passWord.sysOrUser == 1)
    {
        setting.setValue("systemPassword",ui->lineEdit->text());
    }
    else if (passWord.sysOrUser == 0)
    {
        setting.setValue("userPassword",ui->lineEdit->text());
    }
    else if(passWord.sysOrUser == 2)
    {
        passWord.systemPassword = "123456";
        passWord.userPassword = "000000";

        setting.setValue("systemPassword",passWord.systemPassword);
        setting.setValue("userPassword",passWord.userPassword);

    }
    setting.endGroup();
}


