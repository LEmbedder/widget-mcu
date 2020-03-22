#include "formpassword.h"
#include "ui_formpassword.h"

FormPassword::FormPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPassword)
{
    ui->setupUi(this);
    passWord.sysOrUser = -1;
    ui->lineEdit->setMaxLength(15);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$"), this));
    loadPassword();
    isTrue = false;
    type = -1;
}

FormPassword::~FormPassword()
{
    delete ui;
}

void FormPassword::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == passWord.systemPassword)
    {
        passWord.sysOrUser = 1;
        isTrue = true;
        emit emitIsTrue();

        close();
    }
    else if(ui->lineEdit->text() == passWord.userPassword)
    {
        passWord.sysOrUser = 0;
        isTrue = true;
        emit emitIsTrue();
        close();
    }
    else if(ui->lineEdit->text() == SUPERPASSWORD)
    {
        passWord.sysOrUser = 2;
        isTrue = true;
        emit emitIsTrue();
        close();
    }
    else
    {
//        ui->label->setText("密码错误");
        isTrue = false;
    }
    switch (type) {
    case 1:
        emitIsTrue_2();
        break;
    case 2:
        emitIsTrue_3();
        break;
    case 3:
        emitIsTrue_4();
        break;
    case 4:
        emitIsTrue_5();
        break;
    case 5:
        emitIsTrue_6();
        break;
    default:
        break;
    }
    close();

}

void FormPassword::loadPassword()
{
    QString fileName = QApplication::applicationDirPath() + "/password.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("PassWord");
        tagList = setting.childKeys();
        if (tagList.indexOf("systemPassword") != -1)
        {
            passWord.systemPassword = setting.value("systemPassword").toString();
        }
        if (tagList.indexOf("userPassword") != -1)
        {
            passWord.userPassword = setting.value("userPassword").toString();
        }
        setting.endGroup();
    }
    else{
        passWordReset();
    }
}
/*
 * 并初始化\加载\保存密码参数
*/
void FormPassword::passWordReset(void)
{
    passWord.systemPassword = "123456";
    passWord.userPassword = "000000";
    passWord.sysOrUser = -1;/* 不是用户 */
    QString fileName = QApplication::applicationDirPath() + "/password.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("PassWord");
    setting.setValue("systemPassword",passWord.systemPassword);
    setting.setValue("userPassword",passWord.userPassword);
    setting.endGroup();
}

/*
 */
void FormPassword::clearText()
{
    ui->lineEdit->setText("");
}
