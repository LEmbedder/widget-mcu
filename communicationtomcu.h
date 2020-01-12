#ifndef COMMUNICATIONTOMCU_H
#define COMMUNICATIONTOMCU_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include "sys_struct.h"

class communicationToMCU : public QObject
{
    Q_OBJECT
    void initSerialPort();
    void writer(const char *data, qint64 len);
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
    void HcpSetCmdPara(PHCPCMD_SETPARM *pCmd);
    void SendToMcu(const char *data, qint64 len);
    void HcpSetPressure(unsigned short range);
signals:

public slots:
    void receiveInfo();
    void HcpGetDeviceInfo();
};

#endif // COMMUNICATIONTOMCU_H
