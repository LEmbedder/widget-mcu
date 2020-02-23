#include "formprogress.h"
#include "ui_formprogress.h"

#define FOREGROUND   "background-color:rgb(237, 108, 0)"
#define BACKGROUND   "background-color:rgb(0, 132, 142)"
FormProgress::FormProgress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormProgress)
{
    ui->setupUi(this);
    resetProgressValue();
    qDebug()<<"init";
}

FormProgress::~FormProgress()
{
    delete ui;
}
/*
 * 复位颜色
 */
void FormProgress::resetProgressValue()
{
    ui->widget->setStyleSheet(BACKGROUND);
    ui->label->setStyleSheet(BACKGROUND);
    ui->label_2->setStyleSheet(BACKGROUND);

    ui->widget_2->setStyleSheet(BACKGROUND);
    ui->label_3->setStyleSheet(BACKGROUND);
    ui->label_4->setStyleSheet(BACKGROUND);

    ui->widget_3->setStyleSheet(BACKGROUND);
    ui->label_5->setStyleSheet(BACKGROUND);
    ui->label_6->setStyleSheet(BACKGROUND);

    ui->widget_4->setStyleSheet(BACKGROUND);
    ui->label_7->setStyleSheet(BACKGROUND);
    ui->label_8->setStyleSheet(BACKGROUND);

    ui->widget_5->setStyleSheet(BACKGROUND);
    ui->label_9->setStyleSheet(BACKGROUND);
    ui->label_10->setStyleSheet(BACKGROUND);

    ui->widget_6->setStyleSheet(BACKGROUND);
    ui->label_11->setStyleSheet(BACKGROUND);
    ui->label_12->setStyleSheet(BACKGROUND);

    ui->widget_7->setStyleSheet(BACKGROUND);
    ui->label_13->setStyleSheet(BACKGROUND);
    ui->label_14->setStyleSheet(BACKGROUND);

    ui->widget_8->setStyleSheet(BACKGROUND);
    ui->label_15->setStyleSheet(BACKGROUND);
    ui->label_16->setStyleSheet(BACKGROUND);

    ui->widget_9->setStyleSheet(BACKGROUND);
    ui->label_17->setStyleSheet(BACKGROUND);
    ui->label_18->setStyleSheet(BACKGROUND);

    ui->widget_10->setStyleSheet(BACKGROUND);
    ui->label_19->setStyleSheet(BACKGROUND);
    ui->label_20->setStyleSheet(BACKGROUND);

    ui->widget_11->setStyleSheet(BACKGROUND);
    ui->label_21->setStyleSheet(BACKGROUND);
    ui->label_22->setStyleSheet(BACKGROUND);

    ui->widget_12->setStyleSheet(BACKGROUND);
    ui->label_23->setStyleSheet(BACKGROUND);
    ui->label_24->setStyleSheet(BACKGROUND);

    ui->widget_13->setStyleSheet(BACKGROUND);
    ui->label_25->setStyleSheet(BACKGROUND);
    ui->label_26->setStyleSheet(BACKGROUND);

    ui->widget_14->setStyleSheet(BACKGROUND);
    ui->label_29->setStyleSheet(BACKGROUND);

}

/*
 * 设置进度条的值
 */
bool FormProgress::setProgressValue(int value)
{
    resetProgressValue();
    switch (value)
    {
    case 0:
        ui->widget->setStyleSheet(FOREGROUND);
        ui->label->setStyleSheet(FOREGROUND);
        ui->label_2->setStyleSheet(FOREGROUND);
        break;
    case 1:
//        ui->widget_2->setStyleSheet(FOREGROUND);
        ui->label_3->setStyleSheet(FOREGROUND);
        ui->label_4->setStyleSheet(FOREGROUND);
        break;
    case 2:
//        ui->widget_3->setStyleSheet(FOREGROUND);
        ui->label_5->setStyleSheet(FOREGROUND);
        ui->label_6->setStyleSheet(FOREGROUND);
        break;
    case 3:
        ui->widget_4->setStyleSheet(FOREGROUND);
        ui->label_7->setStyleSheet(FOREGROUND);
        ui->label_8->setStyleSheet(FOREGROUND);
        break;
    case 4:
        ui->widget_5->setStyleSheet(FOREGROUND);
        ui->label_9->setStyleSheet(FOREGROUND);
        ui->label_10->setStyleSheet(FOREGROUND);
        break;
    case 5:
        ui->widget_6->setStyleSheet(FOREGROUND);
        ui->label_11->setStyleSheet(FOREGROUND);
        ui->label_12->setStyleSheet(FOREGROUND);
        break;
    case 6:
        ui->widget_7->setStyleSheet(FOREGROUND);
        ui->label_13->setStyleSheet(FOREGROUND);
        ui->label_14->setStyleSheet(FOREGROUND);
        break;
    case 7:
        ui->widget_8->setStyleSheet(FOREGROUND);
        ui->label_15->setStyleSheet(FOREGROUND);
        ui->label_16->setStyleSheet(FOREGROUND);
        break;
    case 8:
        ui->widget_9->setStyleSheet(FOREGROUND);
        ui->label_17->setStyleSheet(FOREGROUND);
        ui->label_18->setStyleSheet(FOREGROUND);
        break;
    case 9:
        ui->widget_10->setStyleSheet(FOREGROUND);
        ui->label_19->setStyleSheet(FOREGROUND);
        ui->label_20->setStyleSheet(FOREGROUND);
        break;
    case 10:
        ui->widget_11->setStyleSheet(FOREGROUND);
        ui->label_21->setStyleSheet(FOREGROUND);
        ui->label_22->setStyleSheet(FOREGROUND);
        break;
    case 11:
        ui->widget_12->setStyleSheet(FOREGROUND);
        ui->label_23->setStyleSheet(FOREGROUND);
        ui->label_24->setStyleSheet(FOREGROUND);
        break;
    case 12:
        ui->widget_13->setStyleSheet(FOREGROUND);
        ui->label_25->setStyleSheet(FOREGROUND);
        ui->label_26->setStyleSheet(FOREGROUND);
        break;
    case 13:
        ui->widget_14->setStyleSheet(FOREGROUND);
        ui->label_29->setStyleSheet(FOREGROUND);
        break;
    default:
        break;
    }
    update();
    return true;
}

/*
 * 设置进度条的值延时的值
 */
void FormProgress::paintEvent(QPaintEvent *event)
{

    int page = systemData.channel_number/16;
    int channel = systemData.channel_number % 16;

    ui->label_2->setText( QString::number(sets[page][channel].time[0]) + "s" );
    ui->label_3->setText( QString::number(sets[page][channel].time[1]) + "s" );
    ui->label_5->setText( QString::number(sets[page][channel].time[2]) + "s" );
    ui->label_7->setText( QString::number(sets[page][channel].time[3]) + "s" );
    ui->label_9->setText( QString::number(sets[page][channel].time[4]) + "s" );
    ui->label_11->setText( QString::number(sets[page][channel].time[5])+ "s");
    ui->label_13->setText( QString::number(sets[page][channel].time[6])+ "s");
    ui->label_15->setText( QString::number(sets[page][channel].time[7])+ "s");
    ui->label_17->setText( QString::number(sets[page][channel].time[8])+ "s");
    ui->label_19->setText( QString::number(sets[page][channel].time[9])+ "s");
    ui->label_21->setText( QString::number(sets[page][channel].time[10])+ "s");
    ui->label_23->setText( QString::number(sets[page][channel].time[11])+ "s");
    ui->label_25->setText( QString::number(sets[page][channel].time[12])+ "s");
}
