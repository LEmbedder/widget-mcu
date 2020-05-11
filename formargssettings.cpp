#include "formargssettings.h"
#include "ui_formargssettings.h"
#include "globalvariable.h"

/* 泄露单位 */
static QString revealUint[][11] = {
    {"Pa", "Pa/s",   "kpa",  "mL/s", "mL/min","L/min","Pa.m^3/s",  "ml/h", "L/h","Sccm"},/*  */
    {"Pa", "Pa/s",   "kPa",  "kPa/s","kPa/min", "mL/s",  "mL/min","mL/min","mL/h","L/h","Sccm"},
    {"mL/s","mL/min","L/min","L/h","m^3/h","mL/h","Pa/min","g/h","Sccm"}
};
static const QString testPressureBigRevealUint[10] = {
    "kPa","kg/cm^2","psi","bar","mbar","Torr","mmH2o","mmHg","MPa",""
};
FormArgsSettings::FormArgsSettings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::FormArgsSettings)
{
    ui->setupUi(this);
//    QWidget::setCursor(QCursor(Qt::BlankCursor));
    setFixedSize(800,480);
    index = 0;
    initParameter();
}

FormArgsSettings::~FormArgsSettings()
{
    delete ui;
}

void FormArgsSettings::initParameter()
{
    /* init */
    modelSelect = 0;
}

/*
 * 更新界面
 */
void FormArgsSettings::updateUI()
{
    ui->lineEditTab1->setText( QString::number(sets->time[0]) );
    ui->lineEditTab2->setText( QString::number(sets->time[1]) );
    ui->lineEditTab3->setText( QString::number(sets->time[2]) );
    ui->lineEditTab4->setText( QString::number(sets->time[3]) );
    ui->lineEditTab5->setText( QString::number(sets->time[4]) );
    ui->lineEditTab6->setText( QString::number(sets->time[5]) );
    ui->lineEditTab7->setText( QString::number(sets->time[6]) );
    ui->lineEditTab8->setText( QString::number(sets->time[7]) );
    ui->lineEditTab9->setText( QString::number(sets->time[8]) );
    ui->lineEditTab10->setText( QString::number(sets->time[9]) );
    ui->lineEditTab11->setText( QString::number(sets->time[10]) );
    ui->lineEditTab12->setText( QString::number(sets->time[11]) );
    ui->lineEditTab13->setText( QString::number(sets->time[12]) );

    ui->lineEdit_revealStandardUpLimit->setText(QString::number(sets->revealStandardUpLimit));
    ui->lineEdit_revealStandardDownLimit->setText(QString::number(sets->revealStandardDownLimit));

    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->removeItem(0);
    }
    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->addItem(revealUint[modelSelect][i]);
    }
    ui->lineEdit_bigRevealStandardValue->setText(QString::number(sets->bigRevealStandardValue));
    ui->lineEdit_testPressure->setText(QString::number(sets->testPressure));
    for(int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->removeItem(0);
    }
    for (int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->addItem(testPressureBigRevealUint[i]);
    }

    ui->lineEdit_testPressureUpLimit->setText(QString::number(sets->testPressureUpLimit));
    ui->lineEdit_testPressureDownLimit->setText(QString::number(sets->testPressureDownLimit));
    ui->lineEdit_measuredVolume->setText(QString::number(sets->measuredVolume));

    ui->lineEdit_standerVolume->setText(QString::number(sets->standerVolume));
    ui->lineEdit_markingTime->setText(QString::number(sets->markingTime));
    ui->lineEdit_channelNumber->setText(QString::number(sets->channelNumber));
    ui->lineEdit_channelDescribe->setText(sets->channelDescribe);

    if(copyPaste.enable == true)
    {
        ui->pushButton_paste->setEnabled(true);
    }
}
/*
 * 更新界面参数
 */
void FormArgsSettings::saveParameter()
{
    sets->time[0] = ui->lineEditTab1->text().toInt();
    sets->time[1] = ui->lineEditTab2->text().toInt();
    sets->time[2] = ui->lineEditTab3->text().toInt();
    sets->time[3] = ui->lineEditTab4->text().toInt();
    sets->time[4] = ui->lineEditTab5->text().toInt();
    sets->time[5] = ui->lineEditTab6->text().toInt();
    sets->time[6] = ui->lineEditTab7->text().toInt();
    sets->time[7] = ui->lineEditTab8->text().toInt();
    sets->time[8] = ui->lineEditTab9->text().toInt();
    sets->time[9] = ui->lineEditTab10->text().toInt();
    sets->time[10] = ui->lineEditTab11->text().toInt();
    sets->time[11] = ui->lineEditTab12->text().toInt();
    sets->time[12] = ui->lineEditTab13->text().toInt();
    sets->revealStandardUpLimit = ui->lineEdit_revealStandardUpLimit->text().toInt();
    sets->revealStandardDownLimit = ui->lineEdit_revealStandardDownLimit->text().toInt();
    if(sets->revealUnit == "")
    {
        sets->revealUnit = revealUint[modelSelect][0];
    }
    else
    {
        sets->revealUnit = ui->comboBox_revealUnit->currentText();
    }
    sets->bigRevealStandardValue = ui->lineEdit_bigRevealStandardValue->text().toInt();
    if(sets->testPressureBigRevealUint == "")
    {
        sets->testPressureBigRevealUint =  testPressureBigRevealUint[0];
    }
    else
    {
        sets->testPressureBigRevealUint = ui->comboBox_testPressureBigRevealUint->currentText();
    }
    sets->testPressure = ui->lineEdit_testPressure->text().toInt();
    sets->testPressureUpLimit = ui->lineEdit_testPressureUpLimit->text().toInt();
    sets->testPressureDownLimit = ui->lineEdit_testPressureDownLimit->text().toInt();
    sets->measuredVolume = ui->lineEdit_measuredVolume->text().toDouble();
    sets->standerVolume =  ui->lineEdit_standerVolume->text().toDouble();
    sets->markingTime = ui->lineEdit_markingTime->text().toInt();
    sets->channelDescribe = ui->lineEdit_channelDescribe->text();
    qDebug()<<ui->lineEdit_channelDescribe->text();
}

/*
 * 设置显示参数
 * 点击按键时更新界面
 */
void FormArgsSettings::setSets(struct SetsPara *set)
{
    sets = set;
    tempsets = sets;
    updateUI();
}

void FormArgsSettings::on_pushButton_delete_clicked()
{
    ui->lineEditTab1->setText( "5" );
    ui->lineEditTab2->setText( "5" );
    ui->lineEditTab3->setText( "5" );
    ui->lineEditTab4->setText( "5" );
    ui->lineEditTab5->setText( "5" );
    ui->lineEditTab6->setText( "5" );
    ui->lineEditTab7->setText( "5" );
    ui->lineEditTab8->setText( "5" );
    ui->lineEditTab9->setText( "5" );
    ui->lineEditTab10->setText( "5");
    ui->lineEditTab11->setText( "5" );
    ui->lineEditTab12->setText( "5" );
    ui->lineEditTab13->setText( "5" );

    ui->lineEdit_revealStandardUpLimit->setText("0");
    ui->lineEdit_revealStandardDownLimit->setText("0");

    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->removeItem(0);
    }
    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->addItem(revealUint[modelSelect][i]);
    }
    ui->lineEdit_bigRevealStandardValue->setText("0");
    ui->lineEdit_testPressure->setText("0");
    for(int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->removeItem(0);
    }
    for (int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->addItem(testPressureBigRevealUint[i]);
    }

    ui->lineEdit_testPressureUpLimit->setText("0");
    ui->lineEdit_testPressureDownLimit->setText("0");
    ui->lineEdit_measuredVolume->setText("0");

    ui->lineEdit_standerVolume->setText("0");
    ui->lineEdit_markingTime->setText("0");
//    ui->lineEdit_channelNumber->setText("1");
    ui->lineEdit_channelDescribe->setText("1");
}

/*
 * 返回保存的参数
 */
void FormArgsSettings::on_pushButton_save_clicked()
{
    saveParameter();
    emit emitSave(sets);
}

void FormArgsSettings::on_pushButton_return_clicked()
{
    close();
//    emit emitClicked(true);
}

/*
 * 复制按键槽函数
 */
void FormArgsSettings::on_pushButton_copy_clicked()
{
    /* 1: 返回当前的参数地址 */
    copyPaste.tempSets = this->tempsets;

    copyPaste.enable = true;
    ui->pushButton_paste->setEnabled(true);

}

/* 粘贴参数 */
void FormArgsSettings::on_pushButton_paste_clicked()
{
    uint tubleNumber = sets->channelNumber;
    this->sets = copyPaste.tempSets;
    updateUI();
    ui->lineEdit_channelNumber->setText(QString::number(tubleNumber));
}
