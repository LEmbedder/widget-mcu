#ifndef PRINTINFORMATION_H
#define PRINTINFORMATION_H

#include <QObject>
#include "autoreplyprint.h"
#include "config.h"

typedef struct Print{
    QString workpiece_number;
    QString worker_number;
    QString device_number;
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
