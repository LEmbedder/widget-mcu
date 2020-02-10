#include "string.h"
#include <sys/ioctl.h>
#include "commthread.h"
#include "globalvariable.h"




//MCU通信线程
void ComThread::run()
{
    struct timeval delay;
    memset((unsigned char*)&delay,0x00,sizeof(timeval));
    threadInit();
    communication = new communicationToMCU;
    communication->HcpSetCmdWordMode(systemData.args_config.model);
    communication->HcpSetCmdProductMode(systemData.args_config.product_model);
    while (true)
    {
        delay.tv_sec = 0;
        delay.tv_usec = 100 * 1000;
        select(0, NULL, NULL, NULL, &delay);
        if(systemData.args_config.model)
        {

        }
        else
        {

        }
    }
 }
