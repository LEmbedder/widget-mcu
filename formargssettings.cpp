#include "formargssettings.h"
#include "ui_formargssettings.h"

/* 泄露单位 */
static QString revealUint[][11] = {
    {"Pa", "Pa/s",   "kpa",  "mL/s", "mL/min","L/min","Pa.m^3/s",  "ml/h", "L/h","Sccm"},/*  */
    {"Pa", "Pa/s",   "kPa",  "kPa/s","kPa/min", "mL/s",  "mL/min","mL/min","mL/h","L/h","Sccm"},
    {"mL/s","mL/min","L/min","L/h","m^3/h","mL/h","Pa/min","g/h","Sccm"}
};
static const QString testPressureBigRevealUint[] = {
    "kPa","kg/cm^2","psi","bar","mbar","Torr","mmH2o","mmHg","MPa",""
};
FormArgsSettings::FormArgsSettings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::FormArgsSettings)
{
    ui->setupUi(this);
//    QWidget::setCursor(QCursor(Qt::BlankCursor));
    setFixedSize(800,480);

    /**/
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

    for (uint i = 0; i < sizeof(sets.time)/sizeof(int); i++)
    {
        sets.time[i] = 5;/* uint s */
    }
    sets.revealStandardUpLimit = 0;
    sets.revealStandardDownLimit = 0;
    sets.revealUnit = "";

    sets.bigRevealStandardValue = 0;
    sets.testPressure = 0;
    sets.testPressureBigRevealUint = "";

    sets.testPressureUpLimit = 0;
    sets.testPressureDownLimit = 0;
    sets.measuredVolume = 0.0;
    sets.standerVolume = 0.0;

    sets.markingTime = 0;/* s */
    sets.channelNumber = 1;
    sets.channelDescribe = "1";
    updateUI();
}

/*
 * 更新界面
 */
void FormArgsSettings::updateUI()
{
    ui->lineEditTab1->setText( QString::number(sets.time[0]) );
    ui->lineEditTab2->setText( QString::number(sets.time[1]) );
    ui->lineEditTab3->setText( QString::number(sets.time[2]) );
    ui->lineEditTab4->setText( QString::number(sets.time[3]) );
    ui->lineEditTab5->setText( QString::number(sets.time[4]) );
    ui->lineEditTab6->setText( QString::number(sets.time[5]) );
    ui->lineEditTab7->setText( QString::number(sets.time[6]) );
    ui->lineEditTab8->setText( QString::number(sets.time[7]) );
    ui->lineEditTab9->setText( QString::number(sets.time[8]) );
    ui->lineEditTab10->setText( QString::number(sets.time[9]) );
    ui->lineEditTab11->setText( QString::number(sets.time[10]) );
    ui->lineEditTab12->setText( QString::number(sets.time[11]) );
    ui->lineEditTab13->setText( QString::number(sets.time[12]) );

    ui->lineEdit_revealStandardUpLimit->setText(QString::number(sets.revealStandardUpLimit));
    ui->lineEdit_revealStandardDownLimit->setText(QString::number(sets.revealStandardDownLimit));

    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->removeItem(0);
    }
    for(int i = 0; revealUint[modelSelect][i] != "";i++ )
    {
        ui->comboBox_revealUnit->addItem(revealUint[modelSelect][i]);
    }
    ui->lineEdit_bigRevealStandardValue->setText(QString::number(sets.bigRevealStandardValue));
    ui->lineEdit_testPressure->setText(QString::number(sets.testPressure));
    for(int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->removeItem(0);
    }
    for (int i = 0; testPressureBigRevealUint[i] != ""; i++)
    {
        ui->comboBox_testPressureBigRevealUint->addItem(testPressureBigRevealUint[i]);
    }

    ui->lineEdit_testPressureUpLimit->setText(QString::number(sets.testPressureUpLimit));
    ui->lineEdit_testPressureDownLimit->setText(QString::number(sets.testPressureDownLimit));
    ui->lineEdit_measuredVolume->setText(QString::number(sets.measuredVolume));

    ui->lineEdit_standerVolume->setText(QString::number(sets.standerVolume));
    ui->lineEdit_markingTime->setText(QString::number(sets.markingTime));
    ui->lineEdit_channelNumber->setText(QString::number(sets.channelNumber));
    ui->lineEdit_channelDescribe->setText(sets.channelDescribe);
}
/*
 * 更新界面参数
 */
void FormArgsSettings::saveParameter()
{
    sets.time[0] = ui->lineEditTab1->text().toInt();
    sets.time[1] = ui->lineEditTab2->text().toInt();
    sets.time[2] = ui->lineEditTab3->text().toInt();
    sets.time[3] = ui->lineEditTab4->text().toInt();
    sets.time[4] = ui->lineEditTab5->text().toInt();
    sets.time[5] = ui->lineEditTab6->text().toInt();
    sets.time[6] = ui->lineEditTab7->text().toInt();
    sets.time[7] = ui->lineEditTab8->text().toInt();
    sets.time[8] = ui->lineEditTab9->text().toInt();
    sets.time[9] = ui->lineEditTab10->text().toInt();
    sets.time[10] = ui->lineEditTab11->text().toInt();
    sets.time[11] = ui->lineEditTab12->text().toInt();
    sets.time[12] = ui->lineEditTab13->text().toInt();

    sets.revealStandardUpLimit = ui->lineEdit_revealStandardUpLimit->text().toInt();
    sets.revealStandardDownLimit = ui->lineEdit_revealStandardDownLimit->text().toInt();

    sets.bigRevealStandardValue = ui->lineEdit_bigRevealStandardValue->text().toInt();
    sets.testPressure = ui->lineEdit_testPressure->text().toInt();

    sets.testPressureUpLimit = ui->lineEdit_testPressureUpLimit->text().toInt();
    sets.testPressureDownLimit = ui->lineEdit_testPressureDownLimit->text().toInt();
    sets.measuredVolume = ui->lineEdit_measuredVolume->text().toDouble();
    sets.standerVolume =  ui->lineEdit_standerVolume->text().toDouble();

    sets.markingTime = ui->lineEdit_markingTime->text().toInt();
    sets.channelDescribe = ui->lineEdit_channelDescribe->text();
}

/*
 * 设置显示参数
 * 点击按键时更新界面
 */
void FormArgsSettings::setSets(struct Sets set)
{
    memcpy(&sets, &set, sizeof(struct Sets));
    updateUI();
}

void FormArgsSettings::on_pushButton_delete_clicked()
{
    initParameter();
    updateUI();
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
    emit emitClicked(true);
}
