#include "string.h"
#include <sys/ioctl.h>
#include "commthread.h"
#include "globalvariable.h"


//Do配置参数
static unsigned int DirectPressureParaDo[BEATS_NUM_MAX] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static unsigned int FlowTypeParaDo[BEATS_NUM_MAX]       ={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static unsigned int DiffPressureParaDo[BEATS_NUM_MAX]   ={0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void ComThread::threadInit(void)
{
    unsigned int i = 0;
    unsigned int m = 0;
    unsigned int n = 0;
    m = systemData.channel_number / 16;
    n = systemData.channel_number % 16;
    if(DIRECT_PRESSURE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            DirectPressurePara[i].DO = DirectPressureParaDo[i];
            DirectPressurePara[i].PFCtaskNum = i;
            DirectPressurePara[i].parmID = 0xFC;
            DirectPressurePara[i].PFCtaskTime = sets[m][n].time[i] * 1000;//秒（s）转化毫秒（ms）
        }
    }
    else if(FLOW_TYPE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            FlowTypePara[i].DO = FlowTypeParaDo[i];
            FlowTypePara[i].PFCtaskNum = i;
            FlowTypePara[i].parmID = 0xFD;
            FlowTypePara[i].PFCtaskTime = sets[m][n].time[i] * 1000;//秒（s）转化毫秒（ms）
        }
    }
    else if(DIFF_PRESSURE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            DiffPressurePara[i].DO = DiffPressureParaDo[i];
            DiffPressurePara[i].PFCtaskNum = i;
            DiffPressurePara[i].parmID = 0xFE;
            DiffPressurePara[i].PFCtaskTime = sets[m][n].time[i] * 1000;//秒（s）转化毫秒（ms）
        }
    }

    systemData.test_press = 0;//测试压
    systemData.press_diff = 0; //差压
    systemData.temp_test_result = 0;
    systemData.set_index = 0;//节拍序号清0


}


void ComThread::DownloadMode(void)
{
    if(systemData.args_config.model != systemData.args_config.model_prv)
    {
         communication->HcpSetCmdWordMode(systemData.args_config.model);
    }
    else
    {}
}

void ComThread::DownloadProductMode(void)
{
    if(systemData.args_config.product_model != systemData.args_config.product_model_prv)
    {
         communication->HcpSetCmdProductMode(systemData.args_config.product_model);
    }
    else
    {}
}

void ComThread::DownloadTestMode(void)
{
    if(systemData.args_config.test_mode != systemData.args_config.test_mode_prv)
    {
        communication->HcpSetCmdProductMode(systemData.args_config.test_mode);
    }
    else
    {}
}

void ComThread::DownloadSetPara(void)
{
    unsigned int i = 0;
    unsigned int Do = 0;
    unsigned char PFCtaskNum = 0;
    unsigned char parmID = 0;
    unsigned int  PFCtaskTime = 0;
    if(DIRECT_PRESSURE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            Do = DirectPressurePara[i].DO;
            PFCtaskNum = DirectPressurePara[i].PFCtaskNum;
            parmID = DirectPressurePara[i].parmID;
            PFCtaskTime = DirectPressurePara[i].PFCtaskTime;
            communication->HcpSetCmdPara(Do,PFCtaskNum,parmID,PFCtaskTime);
        }
    }
    else if(FLOW_TYPE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            Do = FlowTypePara[i].DO;
            PFCtaskNum = FlowTypePara[i].PFCtaskNum;
            parmID = FlowTypePara[i].parmID;
            PFCtaskTime = FlowTypePara[i].PFCtaskTime;
            communication->HcpSetCmdPara(Do,PFCtaskNum,parmID,PFCtaskTime);
        }
    }
    else if(DIFF_PRESSURE_PARA == systemData.args_config.test_mode)
    {
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            Do = DiffPressurePara[i].DO;
            PFCtaskNum = DiffPressurePara[i].PFCtaskNum;
            parmID = DiffPressurePara[i].parmID;
            PFCtaskTime = DiffPressurePara[i].PFCtaskTime;
            communication->HcpSetCmdPara(Do,PFCtaskNum,parmID,PFCtaskTime);
        }
    }
}


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
