/*
 * 主界面的控制
 * 2020年01月01日14:46:46
 */
#include "formmain.h"
#include "ui_formmain.h"
#include <QDebug>
#include <QScrollBar>

#define TEST_FAILED      "background-color:rgb(255,0,0)"
#define TEST_SUCESS      "background-color:rgb(0,255,0)"
FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);
    /* 密码初始化 */
    fps = new FormPassword;
    fps->close();
    connect(fps,SIGNAL(emitIsTrue()),this,SLOT(on_pushButton_4_clicked()));

    save_index = 0;
    /* 容积测试和定标测试模式 */
    formVolumeTest = new FormVolumeTest();
    formVolumeTest->hide();
    formCalibrationTest = new FormCalibrationTest();
    formCalibrationTest->hide();
    ui->widget_12->layout()->addWidget(formVolumeTest);
    ui->widget_12->layout()->addWidget(formCalibrationTest);

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

    /* 打印 */
    printInformation = new PrintInformation;
    formViewData->printInformation = printInformation;
    /* 创建界面结束 */

    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        //qDebug()<<"serialPortName:"<<info.portName();
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
        qDebug("error can't open device /dev/ttyUSB0");
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
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 14);
//    chart->axisX()->setGridLineVisible(false);
    chart->axisY()->setRange(-1000, 1000);
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
    for (uint i = 0; i < sizeof(labelSucess)/sizeof(int); i++)
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

    /* 上下限更新 */
    systemData.up_down_limit.down_limit = -1000;
    systemData.up_down_limit.up_limit = 1000;
    ui->lineEdit_up_limit->setText("1000");
    ui->lineEdit_down_limit->setText("-1000");



    /* 初始化工号 */
    memset(systemData.args_config.work_number,0,30);
    loadConfigArgs();
    ui->lineEdit_channle_number_A->setText(QString::number(systemData.channel_number));
    ui->lineEdit_channle_number_A->setValidator(new QRegExpValidator(QRegExp("([0-9]{2})"), this));
    ui->lineEdit_channle_number_B->setText(QString::number(systemData.channel_number_B));
    ui->lineEdit_channle_number_B->setValidator(new QRegExpValidator(QRegExp("([0-9]{2})"), this));
    updateForm();
}

FormMain::~FormMain()
{
    delete ui;
}
/*
 * 更新最近几次的测试结果显示图片
 * next:新的测试结果
 *  1:成功
 *  0:失败
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
void FormMain::update_mcu()
{
    disp_test_press(systemData.test_press);/* 测试压更新 */
    disp_test_result(systemData.press_diff);/* 差压更新 */
    updateSeries(systemData.set_index,systemData.press_diff);/* 曲线更新 */
    formProgress->setProgressValue(systemData.set_index);/* 进度条更新 */

}
void FormMain::updateForm()
{
    disp_test_press(systemData.test_press);/* 测试压更新 */
    disp_test_result(systemData.press_diff);/* 差压更新 */
    ui->label_worker_number->setText(QString(systemData.args_config.work_number));

    if ( systemData.args_config.test_mode == 0)
    {
        ui->widget_2->show();
        ui->widget_14->show();
        ui->widget_15->show();
        formVolumeTest->hide();
        formCalibrationTest->hide();
        ui->widget_13->setEnabled(true);
    }else if(systemData.args_config.test_mode == 1)
    {
        formVolumeTest->show();
        ui->widget_2->hide();
        ui->widget_14->hide();
        ui->widget_15->hide();
        formCalibrationTest->hide();
        ui->widget_13->setEnabled(false);
    }else if(systemData.args_config.test_mode == 2)
    {
        ui->widget_2->hide();
        ui->widget_14->hide();
        ui->widget_15->hide();
        formCalibrationTest->show();
        formVolumeTest->hide();
        ui->widget_13->setEnabled(false);
    }

}
/*
 * 按键切换为主界面
*/
void FormMain::on_pushButton_clicked()
{
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
    fps->show();
    fps->clearText();
    fps->type = 0;
    if (fps->isTrue == true && fps->type == 0)
    {
        if (passWord.sysOrUser == 1 || passWord.sysOrUser == 0 || passWord.sysOrUser == 2)
        {
            witchButtonChecked(ui->pushButton);
            witchButtonChecked(ui->pushButton_2);
            witchButtonChecked(ui->pushButton_3);
            witchButtonChecked(ui->pushButton_4);

            formArguSetting->close();
            ui->widget_target->close();
            formViewData->close();
            formChannleSettings->show();
        }
    }
    fps->isTrue = false;
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
    /* 工位显示控制 */
    switch (systemData.args_config.worker_space)
    {
    case 0:
        ui->label_workspace_1->setEnabled(true);
        ui->lineEdit_channle_number_A->setEnabled(true);
        ui->label_workspace_2->setEnabled(false);
        ui->lineEdit_channle_number_B->setEnabled(false);
        break;
    case 1:
        ui->label_workspace_1->setEnabled(false);
        ui->lineEdit_channle_number_A->setEnabled(false);
        ui->label_workspace_2->setEnabled(true);
        ui->lineEdit_channle_number_B->setEnabled(true);
        break;
    case 2:
    case 3:
        ui->label_workspace_1->setEnabled(true);
        ui->lineEdit_channle_number_A->setEnabled(true);
        ui->label_workspace_2->setEnabled(true);
        ui->lineEdit_channle_number_B->setEnabled(true);
        break;
    default:
        break;
    }
    updateForm();
}
/* 获取参数
 */
void FormMain::loadConfigArgs()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("SystemData");
        tagList = setting.childKeys();
        if (tagList.indexOf("channel_number") != -1)
        {
            systemData.channel_number = setting.value("channel_number").toInt();
        }
        if (tagList.indexOf("channel_number_B") != -1)
        {
            systemData.channel_number_B = setting.value("channel_number_B").toInt();
        }
        qDebug()<<systemData.channel_number<<systemData.channel_number_B;
    }
}
/*
 * 保存参数
 */

void FormMain::saveConfigArgs()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);
    if(save_index++ > 0)
    {
        setting.beginGroup("SystemData");
        setting.setValue("channel_number",systemData.channel_number);
        setting.setValue("channel_number_B",systemData.channel_number_B);
        if(formProgress != NULL)
            formProgress->update();

    }
}

/*
 * 显示测试压
 */
void FormMain::disp_test_press(double value)
{
    ui->label_test_pressure->setText(QString::number(value,'f',systemData.args_config.test_press_decimal_bit));
}

/*
 *  测试结果
 */
void FormMain::disp_test_result(double value)
{
    ui->label_test_result->setText(QString::number(value,'f',systemData.args_config.reveal_decimal_bit));
}
/* 上限控制 */
void FormMain::on_lineEdit_up_limit_editingFinished()
{
    systemData.up_down_limit.up_limit = ui->lineEdit_up_limit->text().toInt();
    chart->axisY()->setRange(systemData.up_down_limit.down_limit, systemData.up_down_limit.up_limit);
    chart->update();
}

void FormMain::on_lineEdit_down_limit_editingFinished()
{
    systemData.up_down_limit.down_limit = ui->lineEdit_down_limit->text().toInt();
    chart->axisY()->setRange(systemData.up_down_limit.down_limit, systemData.up_down_limit.up_limit);
    chart->update();
}

/*
 * 更新曲线
 * position:运行阶段,也是曲线画点的横坐标
 * value:测试获得的值
 */
void FormMain::updateSeries(int position, double value)
{
    if (series == NULL)
    {
        return;
    }
    if ( position == 0 )
    {
        series->clear();
    }
    if (chart != NULL)
    {
        series->append(position,value);
        chart->update();
    }
}

void FormMain::setViewData(void)
{
    communication->formViewData = formViewData;
    connect(communication,SIGNAL(update_window()),this,SLOT(update_mcu()));
}



void FormMain::on_pushButton_set_channel_number_clicked()
{
    if (ui->lineEdit_channle_number_A->isEnabled())
    {
        if (ui->lineEdit_channle_number_A->text().toInt() < 1)
        {
            ui->lineEdit_channle_number_A->setText(QString::number(1));
        }
        if (ui->lineEdit_channle_number_A->text().toInt() > 64)
        {
            ui->lineEdit_channle_number_A->setText(QString::number(64));
        }
        systemData.channel_number = ui->lineEdit_channle_number_A->text().toInt();
    }
    if (ui->lineEdit_channle_number_B->isEnabled())
    {
        if (ui->lineEdit_channle_number_B->text().toInt() < 1)
        {
            ui->lineEdit_channle_number_B->setText(QString::number(1));
        }
        if (ui->lineEdit_channle_number_B->text().toInt() > 64)
        {
            ui->lineEdit_channle_number_B->setText(QString::number(64));
        }
        systemData.channel_number_B = ui->lineEdit_channle_number_B->text().toInt();
    }
    saveConfigArgs();
}
