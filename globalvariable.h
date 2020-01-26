#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QObject>

struct SystemData{
    int channel_number;//通道号 1-48
};
class GlobalVariable : public QObject
{
    Q_OBJECT
public:
    explicit GlobalVariable(QObject *parent = 0);
    struct SystemData systemData;
signals:

public slots:
};

#endif // GLOBALVARIABLE_H
