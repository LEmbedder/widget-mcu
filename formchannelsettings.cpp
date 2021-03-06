/*
 * 参数设置界面
 */
#include "formchannelsettings.h"
#include "ui_formchannelsettings.h"


FormChannelSettings::FormChannelSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormChannelSettings)
{
    ui->setupUi(this);

    /*
     *  需要加载保持的参数来设置控件参数
     */
    index = 1;
    fcs2_1 = new FormChannleSettings2;
    /* fcs2_1 从文件里加载参数 */
    fcs2_1->initSets(0);
    fcs2_1->loadParam("0");
    fcs2_1->updateChannelDesc();
    ui->verticalLayout_3->addWidget(fcs2_1);

    fcs2_2 = new FormChannleSettings2;
    fcs2_2->initSets(1);
    fcs2_2->loadParam("1");
    fcs2_2->updateChannelDesc();
    ui->verticalLayout_3->addWidget(fcs2_2);
    fcs2_2->close();

    fcs2_3 = new FormChannleSettings2;
    fcs2_3->initSets(2);
    fcs2_3->loadParam("2");
    fcs2_3->updateChannelDesc();
    ui->verticalLayout_3->addWidget(fcs2_3);
    fcs2_3->close();

    fcs2_4 = new FormChannleSettings2;
    fcs2_4->initSets(3);
    fcs2_4->loadParam("3");
    fcs2_4->updateChannelDesc();
    ui->verticalLayout_3->addWidget(fcs2_4);
    fcs2_4->close();

}

FormChannelSettings::~FormChannelSettings()
{
    delete ui;
}

/*
 * 翻页
 */
void FormChannelSettings::on_bt_up_clicked()
{
    QChar tmp[10];
    if(index == 1)
    {
        index = 4;
    }
    else
    {
        index--;
    }
    QString string = ui->lb_index->text();
    tmp[0] = string.at(0);
    tmp[1] = string.at(1);
    tmp[2] = string.at(2);

    tmp[0] = index+'0';
    string = QString(tmp);
    ui->lb_index->setText(string);
//    qDebug("%s",string.toStdString().c_str());
    switchForm();
}
void FormChannelSettings::on_bt_next_clicked()
{
    QChar tmp[10];
    if(index == 4)
    {
        index = 1;
    }
    else
    {
        index++;
    }
    QString string = ui->lb_index->text();
    tmp[0] = string.at(0);
    tmp[1] = string.at(1);
    tmp[2] = string.at(2);

    tmp[0] = index+'0';
    string = QString(tmp);
    ui->lb_index->setText(string);
//    qDebug("%s",string.toStdString().c_str());
    switchForm();

}
void FormChannelSettings::switchForm()
{
    fcs2_1->close();
    fcs2_2->close();
    fcs2_3->close();
    fcs2_4->close();
    switch (index) {
    case 1:
        fcs2_1->show();
        break;
    case 2:
        fcs2_2->show();
        break;
    case 3:
        fcs2_3->show();
        break;
    case 4:
        fcs2_4->show();
        break;
    default:
        break;
    }
}
