#include "communicationtomcu.h"

communicationToMCU::communicationToMCU(QObject *parent) : QObject(parent)
{
    initSerialPort();

}
void communicationToMCU::initSerialPort()
{
    serialPortToMCU = new QSerialPort();

    if ( serialPortToMCU->isOpen() )//如果串口已经打开了 先给他关闭了
    {
        serialPortToMCU->clear();
        serialPortToMCU->close();
    }

    serialPortToMCU->setPortName( "/dev/ttyPS1" );
    if ( !serialPortToMCU->open(QIODevice::ReadOnly) )//用ReadWrite 的模式尝试打开串口
    {
        qDebug("serialPortToMCU error");
    }
    serialPortToMCU->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPortToMCU->setDataBits(QSerialPort::Data8);		//数据位为8位
    serialPortToMCU->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPortToMCU->setParity(QSerialPort::NoParity);	//无校验位
    serialPortToMCU->setStopBits(QSerialPort::OneStop); //一位停止位

    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
    connect(serialPortToMCU,SIGNAL(readyRead()),this,SLOT(receiveInfo()));

}

void communicationToMCU::receiveInfo()
{
    QByteArray info = serialPortToMCU->readAll();

}
