#include "formvolumetest.h"
#include "ui_formvolumetest.h"

FormVolumeTest::FormVolumeTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormVolumeTest)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("([0-9]{5})"), this));
    loadPara();
    updateForm();
}

FormVolumeTest::~FormVolumeTest()
{
    delete ui;
}
void FormVolumeTest::loadPara()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("Config Args");
        tagList = setting.childKeys();
        if (tagList.indexOf("leak_quantity") != -1)
        {
            systemData.args_config.leak_quantity = setting.value("leak_quantity").toInt();
        }
    }
}

void FormVolumeTest::savePara()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("Config Args");
    setting.setValue("leak_quantity",systemData.args_config.leak_quantity);
}
void FormVolumeTest::updateForm()
{
    ui->lineEdit->setText(QString::number(systemData.args_config.leak_quantity));
}
void FormVolumeTest::on_pushButton_ok_clicked()
{
    bool ok;
    int value = 0;
    value  = ui->lineEdit->text().toInt(&ok);
    if (ok )
    {
        systemData.args_config.leak_quantity = value;
        savePara();
    }

}
