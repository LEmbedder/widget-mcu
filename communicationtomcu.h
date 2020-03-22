#ifndef COMMUNICATIONTOMCU_H
#define COMMUNICATIONTOMCU_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include "sys_struct.h"
#include <QTimer>

class communicationToMCU : public QObject
{
    Q_OBJECT
    void initSerialPort();
    void writer(const char *data, qint64 len);
    QTimer *timer,*timer_over,*timer_handle_uart;
    void DownloadMode();
    void DownloadProductMode();
    void DownloadTestMode();
    void HcpHandleKey(unsigned char *puf);
public:
    explicit communicationToMCU(QObject *parent = 0);

    QSerialPort *serialPortToMCU;
    unsigned short crc(unsigned char *pBuf, unsigned short length);
    void HCP_SendACK();
    void HCP_SendNACK(unsigned short why);
    unsigned char *HcpGetTxBuf(void);
    void HcpSendPacket(int length);
    void HcpCmdHandShake();
    void hcpHandleHandShake(unsigned char *puf);
    void HcpSetSaveDefault();
    void HcpSetRestore();
    void HcpSetRestore(unsigned char Hversion[]);
    void HcpSetProductSn(unsigned char sn[]);
    void HcpHandleGetDeviceInfo(unsigned char *puf);
    void HcpSetCmdPara( unsigned int DO,unsigned char PFCtaskNum,unsigned char parmID,unsigned int PFCtaskTime);
    void SendToMcu(const char *data, qint64 len);
    void HcpSetPressure(unsigned short range);
    void HcpSetCmdWordMode(unsigned char WorkMode);
    void HcpSetCmdProductMode(unsigned char ProductMode);
    void start_first();
    void DownloadSetPara();
    void DataInit();
    unsigned int BeatTimerAccm(unsigned int beat_num);
    void beat_do_flag_clear(void);
    int uart_fifo_push(unsigned char data);
    int uart_fifo_pop(unsigned char *data);
    void HandlePacket(unsigned char *puf);
signals:
    void update_window();
public slots:
    void check_stage();
    void receiveInfo();
    void HcpGetDeviceInfo();
    void start_again();
    void HcpProcessPacket();
};

#endif // COMMUNICATIONTOMCU_H
