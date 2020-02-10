#ifndef COMMUNICATIONTOMCU_H
#define COMMUNICATIONTOMCU_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include "sys_struct.h"
#include <QTimer>
#include <QDebug>

class communicationToMCU : public QObject
{
    Q_OBJECT
    void initSerialPort();
    void writer(const char *data, qint64 len);
    QTimer *timer,*timer_over;
    void DataInit();
    void DownloadMode();
    void DownloadProductMode();
    void DownloadTestMode();
    void HcpHandleKey();
public:
    explicit communicationToMCU(QObject *parent = 0);

    QSerialPort *serialPortToMCU;
    unsigned short crc(unsigned char *pBuf, unsigned short length);
    void HCP_SendACK();
    void HCP_SendNACK(unsigned short why);
    unsigned char *HcpGetRxBuf();
    unsigned char *HcpGetTxBuf(void);
    void HcpSendPacket(int length);
    void HcpCmdHandShake();
    void hcpHandleHandShake();
    void HcpSetSaveDefault();
    void HcpSetRestore();
    void HcpSetRestore(unsigned char Hversion[]);
    void HcpSetProductSn(unsigned char sn[]);
    void HcpHandleGetDeviceInfo();
    void HcpProcessPacket();
    void HcpSetCmdPara( unsigned int DO,unsigned char PFCtaskNum,unsigned char parmID,unsigned int PFCtaskTime);
    void SendToMcu(const char *data, qint64 len);
    void HcpSetPressure(unsigned short range);
    void HcpSetCmdWordMode(unsigned char WorkMode);
    void HcpSetCmdProductMode(unsigned char ProductMode);
    void start_first();
    void download_args();
    void DownloadSetPara();
signals:
    void update_window();
public slots:
    void check_stage();
    void receiveInfo();
    void HcpGetDeviceInfo();
    void start_again();
};

#endif // COMMUNICATIONTOMCU_H
