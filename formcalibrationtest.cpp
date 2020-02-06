#include "formcalibrationtest.h"
#include "ui_formcalibrationtest.h"

FormCalibrationTest::FormCalibrationTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCalibrationTest)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("([0-9]{5})"), this));
//    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("^\d+(\.\d+)?$"), this));
    loadPara();
    updateForm();
}

FormCalibrationTest::~FormCalibrationTest()
{
    delete ui;
}
void FormCalibrationTest::loadPara()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("Config Args");
        tagList = setting.childKeys();
        if (tagList.indexOf("demarcate_leak") != -1)
        {
            systemData.args_config.demarcate_leak = setting.value("demarcate_leak").toInt();
        }
        if (tagList.indexOf("demarcate_coefficient") != -1)
        {
            systemData.args_config.demarcate_coefficient = setting.value("demarcate_coefficient").toDouble();
        }
    }
}

void FormCalibrationTest::savePara()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("Config Args");
    setting.setValue("demarcate_leak",systemData.args_config.demarcate_leak);
    setting.setValue("demarcate_coefficient",systemData.args_config.demarcate_coefficient);
}
void FormCalibrationTest::updateForm()
{
    ui->lineEdit->setText(QString::number(systemData.args_config.demarcate_leak));
    ui->lineEdit_2->setText(QString::number(systemData.args_config.demarcate_coefficient,'f',3));
}
/* 复位参数 */
void FormCalibrationTest::on_pushButton_reset_clicked()
{
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("1.000");
}

/* 保存参数
 */
void FormCalibrationTest::on_pushButton_2_clicked()
{
    int value = 0;
    double d_value = 0;
    bool ok;
    value = ui->lineEdit->text().toInt(&ok);
    if (ok)
    {
        systemData.args_config.demarcate_leak = value;
    }
    d_value = ui->lineEdit_2->text().toDouble(&ok);
    if (ok)
    {
        systemData.args_config.demarcate_coefficient = d_value;
        savePara();
    }

}
