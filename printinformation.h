#ifndef PRINTINFORMATION_H
#define PRINTINFORMATION_H

#include <QObject>
#include "autoreplyprint.h"
#include "config.h"

typedef struct Print{
    QString workpiece_number;//工件号
    QString worker_number;   //工号
    QString device_number;   //设备号
    QString result;
    QString timer;
}Print_t;
class PrintInformation : public QObject
{
    Q_OBJECT
public:
    explicit PrintInformation(QObject *parent = 0);

    void print(Print_t *print);
signals:

public slots:
};

#endif // PRINTINFORMATION_H
