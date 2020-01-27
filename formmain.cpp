/*
 * 主界面的控制
 * 2020年01月01日14:46:46
 */
#include "formmain.h"
#include "ui_formmain.h"
#include <QDebug>

#define TEST_FAILED      "background-color:rgb(255,0,0)"
#define TEST_SUCESS      "background-color:rgb(0,255,0)"
FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);
    for(int i = 0; i< 48;i++)
    {
        ui->comboBox_channel_number->addItem(QString::number(i+1));
    }
    /* 选择第一个按键 */
    ui->pushButton->setChecked(true);

    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    /* 创建所有界面显示部分 */
    formChannleSettings = new FormChannelSettings;
    ui->verticalLayout_2->addWidget(formChannleSettings);
    formChannleSettings->close();

    formArguSetting = new FormArguSetting;
    ui->verticalLayout_2->addWidget(formArguSetting);
    connect(formArguSetting->formSystemSetting,SIGNAL(emit_update_config(Args_config*)),
            this,SLOT(update_args_config(Args_config*)));
    /* 显示配置 */
    update_args_config(NULL);
    formArguSetting->close();

    formViewData = new FormViewData;
    ui->verticalLayout_2->addWidget(formViewData);
    formViewData->close();
    /* 创建界面结束 */

    /* 初始化变量 */
    main_Form_Infor.mode             = Mode::AUTO;
    main_Form_Infor.test_pressure    = 12.5445;
    main_Form_Infor.worker_number    = "123456789";
    main_Form_Infor.workpiece_number = "123123123";
    updateForm();

    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();
    }
    serialPort = new QSerialPort();

    if(serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        serialPort->clear();
        serialPort->close();
    }

    serialPort->setPortName( "/dev/ttyUSB0" );
    if( !serialPort->open(QIODevice::ReadOnly) )//用ReadWrite 的模式尝试打开串口
    {
        qDebug("error");
    }
    serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPort->setDataBits(QSerialPort::Data8);		//数据位为8位
    serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPort->setParity(QSerialPort::NoParity);	//无校验位
    serialPort->setStopBits(QSerialPort::OneStop); //一位停止位

    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));

    /*
     * 图标绘制
     */
    series = new QLineSeries();
    series->append(0, 6);
    series->append(1, 4);
    series->append(2, 8);
    series->append(3, 4);
    series->append(4, 5);
    *series << QPointF(5, 1) << QPointF(6, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(9, 2);

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 10);
//    chart->axisX()->setGridLineVisible(false);
    chart->axisY()->setRange(-100, 100);
//    chart->axisY()->setGridLineVisible(false);
    chart->axisX()->setVisible(false);
//    chart->setTitle("Simple line chart example");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setContentsMargins(0, 0, 0, 0);
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundRoundness(0);       //设置背景区域无圆角

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->widget_2->layout()->addWidget(chartView);
    ui->widget_2->show();

    /*
     * 最近几次的测试结果显示
     */
    for (int i = 0; i < sizeof(labelSucess)/sizeof(int); i++)
    {
        labelSucess[i] = 2;
    }
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(0);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(1);
    updateLabelSucess(0);



}

FormMain::~FormMain()
{
    delete ui;
}
/*
 * 更新最近几次的测试结果显示图片
 */
void FormMain::updateLabelSucess(int next)
{
    for (int i = 9; i > 0; i--)
    {
        labelSucess[i] = labelSucess[i-1];
    }
    labelSucess[0] = next;

    if(labelSucess[0] == 1)
    {
        ui->label_sign10->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[0] == 0)
    {
        ui->label_sign10->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[1] == 1)
    {
        ui->label_sign09->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[1] == 0)
    {
        ui->label_sign09->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[2] == 1)
    {
        ui->label_sign08->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[2] == 0)
    {
        ui->label_sign08->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[3] == 1)
    {
        ui->label_sign07->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[3] == 0)
    {
        ui->label_sign07->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[4] == 1)
    {
        ui->label_sign06->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[4] == 0)
    {
        ui->label_sign06->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[5] == 1)
    {
        ui->label_sign05->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[5] == 0)
    {
        ui->label_sign05->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[6] == 1)
    {
        ui->label_sign04->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[6] == 0)
    {
        ui->label_sign04->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[7] == 1)
    {
        ui->label_sign03->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[7] == 0)
    {
        ui->label_sign03->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[8] == 1)
    {
        ui->label_sign02->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[8] == 0)
    {
        ui->label_sign02->setStyleSheet(TEST_FAILED);
    }

    if(labelSucess[9] == 1)
    {
        ui->label_sign01->setStyleSheet(TEST_SUCESS);
    }else if(labelSucess[9] == 0)
    {
        ui->label_sign01->setStyleSheet(TEST_FAILED);
    }

}

void FormMain::receiveInfo()
{
    QByteArray info = serialPort->readAll();
//    qDebug()<<info;
    ui->textEdit_workpiece_number->setText(info.data());
}
void FormMain::updateForm()
{
    ui->label_test_pressure->setText( QString::number(main_Form_Infor.test_pressure) );
    ui->lineEdit_worker_number->setText(main_Form_Infor.worker_number);
    ui->textEdit_workpiece_number->setText(main_Form_Infor.workpiece_number);
//    ui->lineEdit_mode->setText(QString(main_Form_Infor.mode));
}
/*
 * 按键切换为主界面
*/
void FormMain::on_pushButton_clicked()
{
    qDebug()<<"on_pushButton_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formChannleSettings->close();
    formArguSetting->close();
    formViewData->close();
    ui->widget_target->show();

}

/*
 * 按键切换为总设置界面
*/
void FormMain::on_pushButton_2_clicked()
{
    qDebug()<<"on_pushButton_2_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formChannleSettings->close();
    ui->widget_target->close();
    formViewData->close();
    formArguSetting->show();
}

/*
 * 按键切换为数据界面
*/
void FormMain::on_pushButton_3_clicked()
{
    qDebug()<<"on_pushButton_3_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formArguSetting->close();
    ui->widget_target->close();
    formChannleSettings->close();
    formViewData->show();
}
/*
 * 按键切换通道设置界面
*/
void FormMain::on_pushButton_4_clicked()
{
    qDebug()<<"on_pushButton_4_clicked";
    witchButtonChecked(ui->pushButton);
    witchButtonChecked(ui->pushButton_2);
    witchButtonChecked(ui->pushButton_3);
    witchButtonChecked(ui->pushButton_4);

    formArguSetting->close();
    ui->widget_target->close();
    formViewData->close();
    formChannleSettings->show();
}

/*
 * 更改选中后的颜色
*/
void FormMain::witchButtonChecked(QPushButton *button)
{
    if(button->isChecked())
    {
        button->setStyleSheet("background-color: rgb(196, 160, 0);");
    }
    else
    {
        button->setStyleSheet("background-color: rgb(200, 200, 200);");
    }
}

/* 更新设置界面部分 */
void FormMain::update_args_config(struct Args_config* config)
{
    ui->label_select_display->setText(
                formArguSetting->formSystemSetting->return_model()
                );
    ui->label_workspace_1->setText(
                formArguSetting->formSystemSetting->return_worker_space()
                );
    ui->comboBox_channel_number->setCurrentText(QString::number(systemData.channel_number));
}

void FormMain::on_comboBox_channel_number_currentIndexChanged(int index)
{
    // This is available in all editors.
    systemData.channel_number = index-1;
}
