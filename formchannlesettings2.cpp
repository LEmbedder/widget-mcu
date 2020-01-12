#include "formchannlesettings2.h"
#include "ui_formchannlesettings2.h"
#include <QDebug>

FormChannleSettings2::FormChannleSettings2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChannleSettings2)
{
    ui->setupUi(this);
    bt1 = ui->pushButton;
    bt2 = ui->pushButton_2;
    bt3 = ui->pushButton_3;
    bt4 = ui->pushButton_4;
    bt5 = ui->pushButton_5;
    bt6 = ui->pushButton_6;
    bt7 = ui->pushButton_7;
    bt8 = ui->pushButton_8;
    bt9 = ui->pushButton_9;
    bt10 = ui->pushButton_10;
    bt11 = ui->pushButton_11;
    bt12 = ui->pushButton_12;
    bt13 = ui->pushButton_13;
    bt14 = ui->pushButton_14;
    bt15 = ui->pushButton_15;
    bt16 = ui->pushButton_16;
    fas = new FormArgsSettings;
    connect(fas,SIGNAL(emitSave(Sets)),this,SLOT(soltUpdataSets(Sets)));
    initSets();
}

FormChannleSettings2::~FormChannleSettings2()
{
    delete ui;
}
/*
 * 设置当前的是第几个按键弹出的界面
 */
void FormChannleSettings2::soltUpdataSets(struct Sets set)
{
    memcpy(&sets[fas->index],&set,sizeof(struct Sets));
    bt1->setText("1\n2");
    qDebug()<<"set"<<fas->index;
    switch (fas->index) {
    case 0:
        bt1->setText("1\n"+sets[0].channelDescribe);
        break;
    case 1:
        bt1->setText("1\n"+sets[1].channelDescribe);
        break;
    case 2:
        bt1->setText("1\n"+sets[2].channelDescribe);
        break;
    case 3:
        bt1->setText("1\n"+sets[3].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[4].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[5].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[6].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[7].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[8].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[9].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[10].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[11].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[12].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[13].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[14].channelDescribe);
        break;
    case 0:
        bt1->setText("1\n"+sets[15].channelDescribe);
        break;
    default:
        break;
    }
}
/*  */
void FormChannleSettings2::initSets()
{
    for(int i = 0; i < BUTTON_NUMBER; i++)
    {
        memcpy(&sets[i],&fas->sets,sizeof(struct Sets));
    }
}
/*
 * 每个按键都需要加载自己私有的控件属性配置
 */
void FormChannleSettings2::on_pushButton_clicked()
{
    fas->setSets(sets[0]);
    /* 设置当前的是第几个按键弹出的界面 */
    fas->index = 0;
    fas->show();
}
void FormChannleSettings2::on_pushButton_6_clicked()
{
    fas->setSets(sets[1]);
    fas->index = 1;
    fas->show();
}

void FormChannleSettings2::on_pushButton_16_clicked()
{
    fas->setSets(sets[2]);
    fas->index = 2;
    fas->show();
}

void FormChannleSettings2::on_pushButton_3_clicked()
{
    fas->setSets(sets[3]);
    fas->index = 3;
    fas->show();
}

void FormChannleSettings2::on_pushButton_2_clicked()
{
    fas->setSets(sets[4]);
    fas->index = 4;
    fas->show();
}

void FormChannleSettings2::on_pushButton_4_clicked()
{
    fas->setSets(sets[5]);
    fas->index = 5;
    fas->show();
}

void FormChannleSettings2::on_pushButton_5_clicked()
{
    fas->setSets(sets[6]);
    fas->index = 6;
    fas->show();
}

void FormChannleSettings2::on_pushButton_7_clicked()
{
    fas->setSets(sets[7]);
    fas->index = 7;
    fas->show();
}

void FormChannleSettings2::on_pushButton_8_clicked()
{
    fas->setSets(sets[8]);
    fas->index = 8;
    fas->show();
}

void FormChannleSettings2::on_pushButton_10_clicked()
{
    fas->setSets(sets[9]);
    fas->index = 9;
    fas->show();
}

void FormChannleSettings2::on_pushButton_9_clicked()
{
    fas->setSets(sets[10]);
    fas->index = 10;
    fas->show();
}

void FormChannleSettings2::on_pushButton_11_clicked()
{
    fas->setSets(sets[11]);
    fas->index = 11;
    fas->show();
}

void FormChannleSettings2::on_pushButton_12_clicked()
{
    fas->setSets(sets[12]);
    fas->index = 12;
    fas->show();
}

void FormChannleSettings2::on_pushButton_13_clicked()
{
    fas->setSets(sets[13]);
    fas->index = 13;
    fas->show();
}

void FormChannleSettings2::on_pushButton_14_clicked()
{
    fas->setSets(sets[14]);
    fas->index = 14;
    fas->show();
}

void FormChannleSettings2::on_pushButton_15_clicked()
{
    fas->setSets(sets[15]);
    fas->index = 15;
    fas->show();
}
