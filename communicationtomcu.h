#ifndef COMMUNICATIONTOMCU_H
#define COMMUNICATIONTOMCU_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>

class communicationToMCU : public QObject
{
    Q_OBJECT
    void initSerialPort();
public:
    explicit communicationToMCU(QObject *parent = 0);

    QSerialPort *serialPortToMCU;
signals:

public slots:
    void receiveInfo();
};

#endif // COMMUNICATIONTOMCU_H
