#include "formchannlesettings2.h"
#include "ui_formchannlesettings2.h"
#include <QDebug>

FormChannleSettings2::FormChannleSettings2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChannleSettings2)
{
    ui->setupUi(this);
    bt1 = ui->pushButton;
    bt2 = ui->pushButton_02;
    bt3 = ui->pushButton_03;
    bt4 = ui->pushButton_04;
    bt5 = ui->pushButton_05;
    bt6 = ui->pushButton_06;
    bt7 = ui->pushButton_07;
    bt8 = ui->pushButton_08;
    bt9 = ui->pushButton_09;
    bt10 = ui->pushButton_10;
    bt11 = ui->pushButton_11;
    bt12 = ui->pushButton_12;
    bt13 = ui->pushButton_13;
    bt14 = ui->pushButton_14;
    bt15 = ui->pushButton_15;
    bt16 = ui->pushButton_16;
    fas = new FormArgsSettings;
    connect(fas,SIGNAL(emitSave(SetsPara*)),this,SLOT(soltUpdataSets(SetsPara*)));
    connect(fas,SIGNAL(emitSave(SetsPara*)),this,SLOT(savePara()));
    initSets();
}

FormChannleSettings2::~FormChannleSettings2()
{
    delete ui;
}
/*
 * 更行通道描述
 */
void FormChannleSettings2::updateChannelDesc()
{
    bt1->setText("1\n"+sets[0].channelDescribe);
    bt2->setText("2\n"+sets[1].channelDescribe);
    bt3->setText("3\n"+sets[2].channelDescribe);
    bt4->setText("4\n"+sets[3].channelDescribe);
    bt5->setText("5\n"+sets[4].channelDescribe);
    bt6->setText("6\n"+sets[5].channelDescribe);
    bt7->setText("7\n"+sets[6].channelDescribe);
    bt8->setText("8\n"+sets[7].channelDescribe);
    bt9->setText("9\n"+sets[8].channelDescribe);
    bt10->setText("10\n"+sets[9].channelDescribe);
    bt11->setText("11\n"+sets[10].channelDescribe);
    bt12->setText("12\n"+sets[11].channelDescribe);
    bt13->setText("13\n"+sets[12].channelDescribe);
    bt14->setText("14\n"+sets[13].channelDescribe);
    bt15->setText("15\n"+sets[14].channelDescribe);
    bt16->setText("16\n"+sets[15].channelDescribe);
}
/*
 * 设置当前的是第几个按键弹出的界面
 */
void FormChannleSettings2::soltUpdataSets(struct SetsPara *set)
{
    memcpy(&sets[fas->index],set,sizeof(struct SetsPara));
    qDebug()<<"set"<<fas->index;
    switch (fas->index) {
    case 0:
        bt1->setText("1\n"+sets[0].channelDescribe);
        break;
    case 1:
        bt2->setText("2\n"+sets[1].channelDescribe);
        break;
    case 2:
        bt3->setText("3\n"+sets[2].channelDescribe);
        break;
    case 3:
        bt4->setText("4\n"+sets[3].channelDescribe);
        break;
    case 4:
        bt5->setText("5\n"+sets[4].channelDescribe);
        break;
    case 5:
        bt6->setText("6\n"+sets[5].channelDescribe);
        break;
    case 6:
        bt7->setText("7\n"+sets[6].channelDescribe);
        break;
    case 7:
        bt8->setText("8\n"+sets[7].channelDescribe);
        break;
    case 8:
        bt9->setText("9\n"+sets[8].channelDescribe);
        break;
    case 9:
        bt10->setText("10\n"+sets[9].channelDescribe);
        break;
    case 10:
        bt11->setText("11\n"+sets[10].channelDescribe);
        break;
    case 11:
        bt12->setText("12\n"+sets[11].channelDescribe);
        break;
    case 12:
        bt13->setText("13\n"+sets[12].channelDescribe);
        break;
    case 13:
        bt14->setText("14\n"+sets[13].channelDescribe);
        break;
    case 14:
        bt15->setText("15\n"+sets[14].channelDescribe);
        break;
    case 15:
        bt16->setText("16\n"+sets[15].channelDescribe);
        break;
    default:
        break;
    }
}
/*
 * 初始化参数
 */
void FormChannleSettings2::initSets()
{
    for(int i = 0; i < BUTTON_NUMBER; i++)
    {
//        memcpy(&sets[i],&fas->sets,sizeof(struct SetsPara));
        for (uint j = 0; j < sizeof(sets[0].time)/sizeof(int); j++)
        {
            sets[i].time[j] = 5;/* uint s */
        }
        sets[i].revealStandardUpLimit = 0;
        sets[i].revealStandardDownLimit = 0;
        sets[i].revealUnit = "";
        sets[i].bigRevealStandardValue = 0;
        sets[i].testPressure = 0;
        sets[i].testPressureBigRevealUint = "";
        sets[i].testPressureUpLimit = 0;
        sets[i].testPressureDownLimit = 0;
        sets[i].measuredVolume = 0.0;
        sets[i].standerVolume = 0.0;
        sets[i].markingTime = 0;/* s */
        sets[i].channelNumber = 1;
        sets[i].channelDescribe = "1";
    }
}

/*
 * 每个按键都需要加载自己私有的控件属性配置
 */
void FormChannleSettings2::on_pushButton_clicked()
{
    fas->setSets(&sets[0]);
    /* 设置当前的是第几个按键弹出的界面 */
    fas->index = 0;
    fas->show();
}
void FormChannleSettings2::on_pushButton_02_clicked()
{
    fas->setSets(&sets[1]);
    fas->index = 1;
    fas->show();
}

void FormChannleSettings2::on_pushButton_03_clicked()
{
    fas->setSets(&sets[2]);
    fas->index = 2;
    fas->show();
}

void FormChannleSettings2::on_pushButton_04_clicked()
{
    fas->setSets(&sets[3]);
    fas->index = 3;
    fas->show();
}

void FormChannleSettings2::on_pushButton_05_clicked()
{
    fas->setSets(&sets[4]);
    fas->index = 4;
    fas->show();
}

void FormChannleSettings2::on_pushButton_06_clicked()
{
    fas->setSets(&sets[5]);
    fas->index = 5;
    fas->show();
}

void FormChannleSettings2::on_pushButton_07_clicked()
{
    fas->setSets(&sets[6]);
    fas->index = 6;
    fas->show();
}

void FormChannleSettings2::on_pushButton_08_clicked()
{
    fas->setSets(&sets[7]);
    fas->index = 7;
    fas->show();
}

void FormChannleSettings2::on_pushButton_09_clicked()
{
    fas->setSets(&sets[8]);
    fas->index = 8;
    fas->show();
}

void FormChannleSettings2::on_pushButton_10_clicked()
{
    fas->setSets(&sets[9]);
    fas->index = 9;
    fas->show();
}

void FormChannleSettings2::on_pushButton_11_clicked()
{
    fas->setSets(&sets[10]);
    fas->index = 10;
    fas->show();
}

void FormChannleSettings2::on_pushButton_12_clicked()
{
    fas->setSets(&sets[11]);
    fas->index = 11;
    fas->show();
}

void FormChannleSettings2::on_pushButton_13_clicked()
{
    fas->setSets(&sets[12]);
    fas->index = 12;
    fas->show();
}

void FormChannleSettings2::on_pushButton_14_clicked()
{
    fas->setSets(&sets[13]);
    fas->index = 13;
    fas->show();
}

void FormChannleSettings2::on_pushButton_15_clicked()
{
    fas->setSets(&sets[14]);
    fas->index = 14;
    fas->show();
}

void FormChannleSettings2::on_pushButton_16_clicked()
{
    fas->setSets(&sets[15]);
    fas->index = 15;
    fas->show();
}

/*
 * 从文件里加载参数
 * number: 哪个配置项目,一共有4个界面,就有4个配置项目

for(int i = 0; i < BUTTON_NUMBER; i++)
{
//        memcpy(&sets[i],&fas->sets,sizeof(struct SetsPara));
    for (uint j = 0; j < sizeof(sets[0].time)/sizeof(int); i++)
    {
        sets[i].time[j] = 5;
    }
    sets[i].revealStandardUpLimit = 0;
    sets[i].revealStandardDownLimit = 0;
    sets[i].revealUnit = "";
    sets[i].bigRevealStandardValue = 0;
    sets[i].testPressure = 0;
    sets[i].testPressureBigRevealUint = "";
    sets[i].testPressureUpLimit = 0;
    sets[i].testPressureDownLimit = 0;
    sets[i].measuredVolume = 0.0;
    sets[i].standerVolume = 0.0;
    sets[i].markingTime = 0;
    sets[i].channelNumber = 1;
    sets[i].channelDescribe = "1";
}
*/
void FormChannleSettings2::loadParam(QString number)
{
    page = number;
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("page_"+number);
        tagList = setting.childKeys();
        for(int i = 0; i < BUTTON_NUMBER; i++)
        {
            for (uint j = 0; j < sizeof(sets[0].time)/sizeof(int); j++)
            {
                if(tagList.indexOf("set_"+QString::number(i)+"_time_"+QString::number(j)) != -1)
                {
                    sets[i].time[j] = setting.value("set_"+QString::number(i)+"_time_"+QString::number(j)).toInt();
                }
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_revealStandardUpLimit") != -1)
            {
                sets[i].revealStandardUpLimit = setting.value("set_"+QString::number(i)+"_revealStandardUpLimit").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_revealStandardDownLimit") != -1)
            {
                sets[i].revealStandardDownLimit = setting.value("set_"+QString::number(i)+"_revealStandardDownLimit").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_revealUnit") != -1)
            {
                sets[i].revealUnit = setting.value("set_"+QString::number(i)+"_revealUnit").toString();
            }

            if (tagList.indexOf("set_"+QString::number(i)+"_bigRevealStandardValue") != -1)
            {
                sets[i].bigRevealStandardValue = setting.value("set_"+QString::number(i)+"_bigRevealStandardValue").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_testPressure") != -1)
            {
                sets[i].testPressure = setting.value("set_"+QString::number(i)+"_testPressure").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_testPressureBigRevealUintt") != -1)
            {
                sets[i].testPressureBigRevealUint = setting.value("set_"+QString::number(i)+"_testPressureBigRevealUint").toString();
            }

            if (tagList.indexOf("set_"+QString::number(i)+"_testPressureUpLimit") != -1)
            {
                sets[i].testPressureUpLimit = setting.value("set_"+QString::number(i)+"_testPressureUpLimit").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_testPressureDownLimit") != -1)
            {
                sets[i].testPressureDownLimit = setting.value("set_"+QString::number(i)+"_testPressureDownLimit").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_measuredVolume") != -1)
            {
                sets[i].measuredVolume = setting.value("set_"+QString::number(i)+"_measuredVolume").toDouble();
            }

            if (tagList.indexOf("set_"+QString::number(i)+"_standerVolume") != -1)
            {
                sets[i].standerVolume = setting.value("set_"+QString::number(i)+"_standerVolume").toDouble();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_markingTime") != -1)
            {
                sets[i].markingTime = setting.value("set_"+QString::number(i)+"_markingTime").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_channelNumber") != -1)
            {
                sets[i].channelNumber = setting.value("set_"+QString::number(i)+"_channelNumber").toInt();
            }
            if (tagList.indexOf("set_"+QString::number(i)+"_channelDescribe") != -1)
            {
                sets[i].channelDescribe = setting.value("set_"+QString::number(i)+"_channelDescribe").toString();
            }
        }
        setting.endGroup();
    }
}
/*
 * 保存配置的参数到ini文件里
 */
void FormChannleSettings2::savePara()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("page_"+page);
    for(int i = 0; i < BUTTON_NUMBER; i++)
    {
        for (uint j = 0; j < sizeof(sets[0].time)/sizeof(int); j++)
        {
//            if(tagList.indexOf("set_"+QString::number(i)+"_time_"+QString::number(j)) != -1)
            {
                //sets[i].time[j] = setting.value("set_"+QString::number(i)+"_time_"+QString::number(j)).toInt();
                setting.setValue("set_"+QString::number(i)+"_time_"+QString::number(j),((sets[i].time[j])));
            }
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_revealStandardUpLimit") != -1)
        {
//            sets[i].revealStandardUpLimit = setting.value("set_"+QString::number(i)+"_revealStandardUpLimit").toInt();
            setting.setValue("set_"+QString::number(i)+"_revealStandardUpLimit",(sets[i].revealStandardUpLimit));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_revealStandardDownLimit") != -1)
        {
//            sets[i].revealStandardDownLimit = setting.value("set_"+QString::number(i)+"_revealStandardDownLimit").toInt();
            setting.setValue("set_"+QString::number(i)+"_revealStandardDownLimit",(sets[i].revealStandardDownLimit));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_revealUnit") != -1)
        {
//            sets[i].revealUnit = setting.value("set_"+QString::number(i)+"_revealUnit").toString();
            setting.setValue("set_"+QString::number(i)+"_revealUnit",(sets[i].revealUnit));
        }

//        if (tagList.indexOf("set_"+QString::number(i)+"_bigRevealStandardValue") != -1)
        {
//            sets[i].bigRevealStandardValue = setting.value("set_"+QString::number(i)+"_bigRevealStandardValue").toInt();
            setting.setValue("set_"+QString::number(i)+"_bigRevealStandardValue",(sets[i].bigRevealStandardValue));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_testPressure") != -1)
        {
//            sets[i].testPressure = setting.value("set_"+QString::number(i)+"_testPressure").toInt();
            setting.setValue("set_"+QString::number(i)+"_testPressure",(sets[i].testPressure));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_testPressureBigRevealUint") != -1)
        {
//            sets[i].testPressureBigRevealUint = setting.value("set_"+QString::number(i)+"_testPressureBigRevealUint").toString();
            setting.setValue("set_"+QString::number(i)+"_testPressureBigRevealUint",(sets[i].testPressureBigRevealUint));
        }

//        if (tagList.indexOf("set_"+QString::number(i)+"_testPressureUpLimit") != -1)
        {
//            sets[i].testPressureUpLimit = setting.value("set_"+QString::number(i)+"_testPressureUpLimit").toInt();
            setting.setValue("set_"+QString::number(i)+"_testPressureUpLimit",(sets[i].testPressureUpLimit));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_testPressureDownLimit") != -1)
        {
//            sets[i].testPressureDownLimit = setting.value("set_"+QString::number(i)+"_testPressureDownLimit").toInt();
            setting.setValue("set_"+QString::number(i)+"_testPressureDownLimit",(sets[i].testPressureDownLimit));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_measuredVolume") != -1)
        {
//            sets[i].measuredVolume = setting.value("set_"+QString::number(i)+"_measuredVolume").toDouble();
            setting.setValue("set_"+QString::number(i)+"_measuredVolume",(sets[i].measuredVolume));
        }

//        if (tagList.indexOf("set_"+QString::number(i)+"_standerVolume") != -1)
        {
//            sets[i].standerVolume = setting.value("set_"+QString::number(i)+"_standerVolume").toDouble();
            setting.setValue("set_"+QString::number(i)+"_standerVolume",(sets[i].standerVolume));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_markingTime") != -1)
        {
//            sets[i].markingTime = setting.value("set_"+QString::number(i)+"_markingTime").toInt();
            setting.setValue("set_"+QString::number(i)+"_markingTime",(sets[i].markingTime));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_channelNumber") != -1)
        {
//            sets[i].channelNumber = setting.value("set_"+QString::number(i)+"_channelNumber").toInt();
            setting.setValue("set_"+QString::number(i)+"_channelNumber",(sets[i].channelNumber));
        }
//        if (tagList.indexOf("set_"+QString::number(i)+"_channelDescribe") != -1)
        {
//            sets[i].channelDescribe = setting.value("set_"+QString::number(i)+"_channelDescribe").toString();
            setting.setValue("set_"+QString::number(i)+"_channelDescribe",(sets[i].channelDescribe));
        }
    }
    setting.endGroup();
}
