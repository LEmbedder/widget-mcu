#ifndef COMMTHREAD_H
#define COMMTHREAD_H


#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QTime>
#include "communicationtomcu.h"


//系统数据线程定义
class ComThread : public QThread
{
    Q_OBJECT
    void DownloadMode();
    void DownloadProductMode();
    void DownloadTestMode();
    void threadInit();
    void DownloadSetPara();
public:
        virtual void run();
       communicationToMCU *communication;

 };

#endif // COMMTHREAD_H)
