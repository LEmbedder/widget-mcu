#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "sys_struct.h"
#include "communicationtomcu.h"
#include "globalvariable.h"



#define HCP_PDUOFFSET         0xaa     //包头标志
#define BEAT_DO_FLAG_START    0xaa  
#define BEAT_DO_FLAG_STOP     0x55  

/*
bit4  LED（合格）对应开关量输出通道掩码
bit5  LED（测试端不合格）对应开关量输出通道掩码
bit6  LED（参考端不合格）对应开关量输出通道掩码

bit8  value（充气）对应开关量输出通道掩码
bit9  value（平衡）对应开关量输出通道掩码
bit10  value（放气）对应开关量输出通道掩码
bit11  value（负压）对应开关量输出通道掩码

bit27 对应蜂鸣器开关量输出通道掩码
*/
//Do配置参数
//1.待机    2.延时1     3.延时2     4.延时3     5.充气    6.泄压      7.平衡1       8.平衡2    9.测试     10.排气    11.延时4   12.延时5 13.结束



//CCITT模式CRC余式表
static const unsigned short int CRC_Table[256] =
{
    0X0000,0X1021,0X2042,0X3063,0X4084,0X50A5,0X60C6,0X70E7,0X8108,0X9129,0XA14A,0XB16B,0XC18C,0XD1AD,0XE1CE,0XF1EF,
    0X1231,0X0210,0X3273,0X2252,0X52B5,0X4294,0X72F7,0X62D6,0X9339,0X8318,0XB37B,0XA35A,0XD3BD,0XC39C,0XF3FF,0XE3DE,
    0X2462,0X3443,0X0420,0X1401,0X64E6,0X74C7,0X44A4,0X5485,0XA56A,0XB54B,0X8528,0X9509,0XE5EE,0XF5CF,0XC5AC,0XD58D,
    0X3653,0X2672,0X1611,0X0630,0X76D7,0X66F6,0X5695,0X46B4,0XB75B,0XA77A,0X9719,0X8738,0XF7DF,0XE7FE,0XD79D,0XC7BC,
    0X48C4,0X58E5,0X6886,0X78A7,0X0840,0X1861,0X2802,0X3823,0XC9CC,0XD9ED,0XE98E,0XF9AF,0X8948,0X9969,0XA90A,0XB92B,
    0X5AF5,0X4AD4,0X7AB7,0X6A96,0X1A71,0X0A50,0X3A33,0X2A12,0XDBFD,0XCBDC,0XFBBF,0XEB9E,0X9B79,0X8B58,0XBB3B,0XAB1A,
    0X6CA6,0X7C87,0X4CE4,0X5CC5,0X2C22,0X3C03,0X0C60,0X1C41,0XEDAE,0XFD8F,0XCDEC,0XDDCD,0XAD2A,0XBD0B,0X8D68,0X9D49,
    0X7E97,0X6EB6,0X5ED5,0X4EF4,0X3E13,0X2E32,0X1E51,0X0E70,0XFF9F,0XEFBE,0XDFDD,0XCFFC,0XBF1B,0XAF3A,0X9F59,0X8F78,
    0X9188,0X81A9,0XB1CA,0XA1EB,0XD10C,0XC12D,0XF14E,0XE16F,0X1080,0X00A1,0X30C2,0X20E3,0X5004,0X4025,0X7046,0X6067,
    0X83B9,0X9398,0XA3FB,0XB3DA,0XC33D,0XD31C,0XE37F,0XF35E,0X02B1,0X1290,0X22F3,0X32D2,0X4235,0X5214,0X6277,0X7256,
    0XB5EA,0XA5CB,0X95A8,0X8589,0XF56E,0XE54F,0XD52C,0XC50D,0X34E2,0X24C3,0X14A0,0X0481,0X7466,0X6447,0X5424,0X4405,
    0XA7DB,0XB7FA,0X8799,0X97B8,0XE75F,0XF77E,0XC71D,0XD73C,0X26D3,0X36F2,0X0691,0X16B0,0X6657,0X7676,0X4615,0X5634,
    0XD94C,0XC96D,0XF90E,0XE92F,0X99C8,0X89E9,0XB98A,0XA9AB,0X5844,0X4865,0X7806,0X6827,0X18C0,0X08E1,0X3882,0X28A3,
    0XCB7D,0XDB5C,0XEB3F,0XFB1E,0X8BF9,0X9BD8,0XABBB,0XBB9A,0X4A75,0X5A54,0X6A37,0X7A16,0X0AF1,0X1AD0,0X2AB3,0X3A92,
    0XFD2E,0XED0F,0XDD6C,0XCD4D,0XBDAA,0XAD8B,0X9DE8,0X8DC9,0X7C26,0X6C07,0X5C64,0X4C45,0X3CA2,0X2C83,0X1CE0,0X0CC1,
    0XEF1F,0XFF3E,0XCF5D,0XDF7C,0XAF9B,0XBFBA,0X8FD9,0X9FF8,0X6E17,0X7E36,0X4E55,0X5E74,0X2E93,0X3EB2,0X0ED1,0X1EF0
};

#define BUF_RXD_SIZE 1024

uint16_t data_in  = 0;
uint16_t data_out = 0;

static unsigned char buf_rxd[BUF_RXD_SIZE];     //uart通信接口接收缓冲区
static unsigned char hcp_txBuf[HCP_TXBUFLEN];     //uart通信接口发送缓冲区
unsigned char data_buf[BUF_RXD_SIZE] = {0};
unsigned char hcp_rxBuf_len = 0;    //接收长度
unsigned char hcp_txBuf_len = 0;    //发送长度

unsigned short int HCP_sn = 0;

communicationToMCU::communicationToMCU(QObject *parent) : QObject(parent)
{
    initSerialPort();
    /* 新建定时器用于定时检查 */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(check_stage()));
    timer->start(300);// 启动定时器ms

    timer_handle_uart = new QTimer(this);
    connect(timer_handle_uart, SIGNAL(timeout()), this, SLOT( HcpProcessPacket()));
    timer_handle_uart->start(10);// 启动定时器ms

    /* 单次执行,最终节拍结束后执行 */
    timer_over = new QTimer(this);
    timer_over->setSingleShot(true);
    connect(timer_over, SIGNAL(timeout()), this, SLOT(start_again()));
    memset(hcp_txBuf,0x00,HCP_TXBUFLEN);
    memset(buf_rxd,0x00,BUF_RXD_SIZE);
    //formViewData->printInformation->print();
    //timer_over->start(1000);// 启动定时器ms

}
void communicationToMCU::initSerialPort()
{
    serialPortToMCU = new QSerialPort();

    if ( serialPortToMCU->isOpen() )//如果串口已经打开了 先给他关闭了
    {
        serialPortToMCU->clear();
        serialPortToMCU->close();
    }

    serialPortToMCU->setPortName( "/dev/ttySAC4" );
    if ( !serialPortToMCU->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug("serialPortToMCU error");
    }
    else
    {
        qDebug("serial port open success!\n");
    }
    serialPortToMCU->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serialPortToMCU->setDataBits(QSerialPort::Data8);		//数据位为8位
    serialPortToMCU->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serialPortToMCU->setParity(QSerialPort::NoParity);	//无校验位
    serialPortToMCU->setStopBits(QSerialPort::OneStop); //一位停止位

    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
    connect(serialPortToMCU,SIGNAL(readyRead()),this,SLOT(receiveInfo()));

}

void communicationToMCU::receiveInfo()
{
    char *tmp = NULL;
    QByteArray info = serialPortToMCU->readAll();
    tmp = info.data();
    for(int i = 0; i < info.length(); i++)
    {
        printf("0x%02x  ",tmp[i]);
        uart_fifo_push(tmp[i]) ;
    }
    printf("\n");
}

void communicationToMCU::SendToMcu(const char *data, qint64 len)
{
    serialPortToMCU->write(data,len);
}


/*---------------------------------------------------------------------------------------
 函数原型:  unsigned char *HCP_GetTxBuf(void)
 功    能:  根据当前通信端口（HCP_host）获取该通信端口接收缓冲区地址
 输入参数:  NA
 输出参数:  NA
 返 回 值: 接收缓冲区指针
 注意事项：  
---------------------------------------------------------------------------------------*/
unsigned char *communicationToMCU::HcpGetTxBuf(void)
{
    unsigned char *pTxBuf = NULL;
    pTxBuf = hcp_txBuf;
    return pTxBuf;
}
/*---------------------------------------------------------------------------------------
 函数原型:  unsigned short int CRC(char *pBuf,INT16 length)
 功    能:  对pBuf中的字节流进行CRC计算
 输入参数:	1、pBuf:输入字节流缓冲区
            2、length:字节流长度
 输出参数:	NA
 返 回 值:	CRC校验码
 注意事项：	NA
---------------------------------------------------------------------------------------*/
unsigned short int communicationToMCU::crc(unsigned char *pBuf,unsigned short int length)
{
    register int i = 0;
    unsigned char tmp  = 0;
    unsigned short int crc_tmp = 0;
    for(i=0;i <length;i++)
    {
        tmp = pBuf[i] ^ (crc_tmp >> 8);
        crc_tmp = crc_tmp<<8;
        crc_tmp ^= CRC_Table[tmp];
    }
    return crc_tmp;
}

/*---------------------------------------------------------------------------------------
 函数原型:  void HCP_SendACK(void)
 功    能:  发送ACK_YESSIR应答包
 输入参数:	NA
 输出参数:	NA
 返 回 值:	NA
 注意事项：
---------------------------------------------------------------------------------------*/

void communicationToMCU::HCP_SendACK(void)
{
    PHCPACK pAck;
    pAck =(PHCPACK)HcpGetTxBuf();

    if(pAck == NULL)
    {
    return;
    }

    pAck->pduOffset = HCP_PDUOFFSET;
    pAck->type = ACK_PACKET;
    pAck->sn = HCP_sn;
    pAck->len = sizeof(HCPACK);
    pAck->ack = ACK_YESSIR;
    HcpSendPacket(sizeof(HCPACK));
}

/*---------------------------------------------------------------------------------------
 函数原型:  void HCP_SendNACK(UINT16 why)
 功    能:  发送ACK_NACK应答包
 输入参数:	NA
 输出参数:	NA
 返 回 值:	NA
 注意事项：
---------------------------------------------------------------------------------------*/
void communicationToMCU::HCP_SendNACK(unsigned short int why)
{

    PHCPACK_NACK pAck;
    pAck = (PHCPACK_NACK)HcpGetTxBuf();

    if(NULL == pAck)
    {
        return;
    }

    pAck->pduOffset = HCP_PDUOFFSET;
    pAck->type = ACK_PACKET;
    if(why == NACK_WHY_BADCRC)
    {
        pAck->sn = 0x0000;
    }
    else
    {
        pAck->sn = HCP_sn;
    }
    pAck->len = sizeof(HCPACK_NACK);
    pAck->ack = ACK_NACK;
    pAck->why = why;
    HcpSendPacket(sizeof(HCPACK_NACK));
}


/*---------------------------------------------------------------------------------------
 函数原型:  void HcpSendPacket(int length)
 功    能:  根据当前主机通信端口，给应答包做CRC校验后发出
 输入参数:	1、length，待发送包的长度，不包含CRC字段
 输出参数:	NA
 返 回 值:	NA
 注意事项：
---------------------------------------------------------------------------------------*/
void communicationToMCU::HcpSendPacket(int length)
{
    unsigned short int tmp = 0;
    unsigned char *pTxBuf = NULL;
    pTxBuf = hcp_txBuf;
    tmp = crc(pTxBuf,length);       //计算CRC值
    pTxBuf[length++] = (tmp>>8) & 0xFF;
    pTxBuf[length++] = tmp & 0xFF;
    hcp_txBuf_len = length;

    printf("send--------------------------------------------------------------\n");
    printf("hcp_txBuf_len =%d\n",hcp_txBuf_len);
    for(int i = 0; i < hcp_txBuf_len; i++)
        printf("0x%02x  ",pTxBuf[i]);
    printf("\n");
    SendToMcu((char *)pTxBuf,hcp_txBuf_len);
}

//握手
void communicationToMCU::HcpCmdHandShake(void)
{
    HCPACK_ALIVE_CMD pAck;
    memset((unsigned char *)&pAck,0x00,sizeof(HCPACK_ALIVE_CMD));
    pAck.header.pduOffset = HCP_PDUOFFSET;
    pAck.header.type      = ACK_PACKET;
    pAck.header.sn        = HCP_sn;
    pAck.header.len   = sizeof(HCPACK_ALIVE_CMD);
    pAck.header.cmd = CMD_HANDSHAKE;
    memcpy(hcp_txBuf,(unsigned char *)&pAck,sizeof(HCPACK_ALIVE_CMD));
    HcpSendPacket(sizeof(HCPACK_ALIVE_CMD));
}


//测试结果写入数据库
//beat_index 节拍序号
void communicationToMCU::WriteTestResultToDb(unsigned int revealStandardUpLimit,unsigned int revealStandardDownLimit,\
                                             QString revealUnit,unsigned char testResult,\
                                             QString testPressureBigRevealUint,\
                                             unsigned int  PFCtaskTime)
{
    struct tm ptm;
    time_t tNow =time ( NULL);
    memset((struct tm*)&ptm,0x00,sizeof(struct tm));
    localtime_r ( &tNow, &ptm );
    char buff[128] = {0};
    sprintf (buff,"%d.%d.%d-%d:%d:%d\n",ptm.tm_year+1900,ptm.tm_mon+1,ptm.tm_mday,ptm.tm_hour,ptm.tm_min,ptm.tm_sec);
    formViewData->insertDatabase( QString(QLatin1String(systemData.args_config.work_number)),\
                                 QString::number(systemData.args_config.worker_space),\
                                 QString(QLatin1String(buff)),\
                                 revealStandardUpLimit,\
                                 revealStandardDownLimit,\
                                 revealUnit,\
                                 QString::number(testResult),\
                                 testPressureBigRevealUint,\
                                 PFCtaskTime);
}

int communicationToMCU::hcpHandleProccess(unsigned char beat_index,double press_diff)
{
    int ret = 0;
    unsigned int j = 0;
    unsigned char is_write_to_db = 0x55;
    unsigned int  PFCtaskTime;
    unsigned int revealStandardUpLimit;//泄露标准上限
    unsigned int revealStandardDownLimit;//泄露标准下限
    QString revealUnit;   //泄露单位unsigned int  PFCtaskTime
    QString testPressureBigRevealUint;//测试压单位
    unsigned int bigRevealStandardValue;//大泄露标准值
    unsigned int testPressureUpLimit;//测试压上限
    unsigned int testPressureDownLimit;//测试压下限
    unsigned char testResult = 0;
    if(beat_index > 0)
    {
        for(j = 0; j < HCP_PARA_SET_NUM; j++)
        {
            if(HCP_SET_PARA_SEND_FLAG_ING == HcpSetPara[j].send_flag)
            {
                PFCtaskTime = HcpSetPara[j].ParaSet[beat_index - 1].PFCtaskTime;
                revealStandardUpLimit   = HcpSetPara[j].ParaSet[beat_index - 1].revealStandardUpLimit ;
                revealStandardDownLimit = HcpSetPara[j].ParaSet[beat_index - 1].revealStandardDownLimit;
                revealUnit = HcpSetPara[j].ParaSet[beat_index - 1].revealUnit;
                testPressureBigRevealUint = HcpSetPara[j].ParaSet[beat_index - 1].testPressureBigRevealUint;
                bigRevealStandardValue = HcpSetPara[j].ParaSet[beat_index - 1].bigRevealStandardValue;
                testPressureUpLimit = HcpSetPara[j].ParaSet[beat_index - 1].testPressureUpLimit;
                testPressureDownLimit = HcpSetPara[j].ParaSet[beat_index - 1].testPressureDownLimit;
            }
            else
            {}
        }
    }
    else
    {}
    switch(beat_index)
    {
        case BEAT_STANDBY:
            systemData.press_diff = 0;
            break;
        case BEAT_DELAY_ONE:
            systemData.press_diff = 0;
            break;
        case BEAT_DELAY_TWO:
            systemData.press_diff = 0;
            break;
        case BEAT_DELAY_THREE:
            systemData.press_diff = 0;
            break;
        case BEAT_INFLATABLE://充气
            systemData.press_diff = 0;
//            if( systemData.test_press > testPressureUpLimit)//超过上限\报警、写数据库、(直接排气流程)
//            {
//                is_write_to_db = 0xaa;
//                testResult = TEST_FAILURE_UPPER_RANGE;
//                ret = -1;
//            }
//            else
//            {
//            }
            break;
        case BEAT_PRESSURE_RELIEF:
            systemData.press_diff = 0;
            if( systemData.test_press < testPressureDownLimit)//超过下限\报警、写数据库、(直接排气流程)
            {
                is_write_to_db = 0xaa;
                testResult = TEST_FAILURE_PRESS_UPPER_LIMIT;
                ret = -1;
            }
            else
            {
            }
            break;
        case BEAT_BALANCE_ONE:
        case BEAT_BALANCE_TWO:
             systemData.press_diff = press_diff;
             if( systemData.test_press > bigRevealStandardValue)//大漏\报警、写数据库、(直接排气流程)
             {
                 is_write_to_db = 0xaa;
                 testResult = TEST_FAILURE_BIG_LEAK;
                 ret = -1;
             }
             else
             {
             }
             //目前没有做
             //测试超量程上限，超量程下限(主要针对差压传感器)
             //报警、写数据库、(直接排气流程)
             break;
        case BEAT_TEST:
            systemData.press_diff = press_diff;
            if((systemData.press_diff < revealStandardUpLimit)
                && (systemData.press_diff > revealStandardDownLimit))
            {
                is_write_to_db = 0xaa;
                testResult = TEST_PASS;
            }
            else if(systemData.press_diff >= revealStandardUpLimit)
            {
                is_write_to_db = 0xaa;
                testResult = TEST_FAILURE_NG_PLUS;
                ret = -1;
            }
            else
            {
                is_write_to_db = 0xaa;
                testResult = TEST_FAILURE_NG_MINUS;
                ret = -1;
            }
            break;
        default:
            //测试完之后，一直保持测试结果，不做数据更新。
            //下次重新开启测试，数据清零
            break;
    }

    if(0xaa == is_write_to_db)
    {
        WriteTestResultToDb(revealStandardUpLimit,revealStandardDownLimit,revealUnit,\
                            testResult,testPressureBigRevealUint,PFCtaskTime);
    }
    else
    {
    }
    return ret;
}

//处理应答包
void communicationToMCU::hcpHandleHandShake(unsigned char *puf)
{
    unsigned int j = 0;
    unsigned int send_flag = 0;
    unsigned int flag = 0;
    unsigned int beat_time = 0;
    unsigned  int      timeBase = 0;       //测试流程时间基准
    unsigned short int      writePos = 0;       //数据缓冲区(差压)当前写入位置
    unsigned short int      sample1 = 0;        //直压采样值
    unsigned short int      currStepSample2 = 0;//当前节拍差压采样值
    unsigned short int      lastStepSample1 = 0;//上一节拍直压采样值
    unsigned short int      lastStepSample2 = 0;//上一节拍差压采样值
    unsigned short int      lastStepNum = 0;    //上一节拍编号
    double  press_diff = 0;
    timeBase = puf[6] | puf[7] << 8 | puf[8] << 16 | puf[9] << 24;
    writePos = puf[10] | puf[11] << 8;
    sample1  = puf[12] | puf[13] << 8;
    currStepSample2 = puf[14] | puf[15] << 8;
    lastStepSample1 = puf[16] | puf[17] << 8;
    lastStepSample2 = puf[18] | puf[19] << 8;
    lastStepNum     = puf[20] | puf[21] << 8;

    printf("timeBase =%d\n",timeBase);
    printf("writePos =%d\n",writePos);
    printf("sample1 =%d\n",sample1);
    printf("currStepSample2 =%d\n",currStepSample2);
    printf("lastStepSample1 =%d\n",lastStepSample1);
    printf("lastStepSample2 =%d\n",lastStepSample2);
    printf("lastStepNum =%d\n",lastStepNum);

    systemData.test_press = 4.11 * sample1 / 65536 * 180.5485 - 142.0543;     //直压采样值
    press_diff = 4.11 * currStepSample2 / 65536 * 587.54375  - 1414.78125;     //当前节拍差压采样值
    systemData.set_index  = lastStepNum ;      //节拍编号
    beat_time = BeatTimerAccm(systemData.set_index);//已执行节拍时间累加
    systemData.time_remaining = beat_time - timeBase;

    printf("beat_time = %d\n",beat_time);
    printf("systemData.set_index = %d\n",systemData.set_index);
    printf("systemData.time_remaining = %d\n",systemData.time_remaining);
    if(systemData.time_remaining < 0)
    {
        systemData.time_remaining = 0;
    }
    else
    {}
  
    if((systemData.set_index > 0) && (systemData.set_index < BEATS_NUM_MAX)
        && (BEAT_DO_FLAG_START == systemData.beat_do_flag[systemData.set_index]))
    {
        systemData.beat_do_flag[systemData.set_index] = BEAT_DO_FLAG_STOP;
    }
    else
    {}
    if(hcpHandleProccess(systemData.set_index,press_diff) < 0)
    {
        systemData.set_index = BEATS_NUM_MAX;
        memset(systemData.beat_do_flag,BEAT_DO_FLAG_STOP,BEATS_NUM_MAX);
    }
    else
    {}
    if(BEATS_NUM_MAX == systemData.set_index) 
    {
        systemData.time_remaining = 0;
        systemData.temp_test_result = systemData.press_diff;
        systemData.BeatState        = BEAT_STATE_STOP;

        for(j = 0; j < HCP_PARA_SET_NUM; j++)
        {
            if((HCP_SET_PARA_FLAG_ON == HcpSetPara[j].flag)
                && (HCP_SET_PARA_SEND_FLAG_ING == HcpSetPara[j].send_flag))
            {
                HcpSetPara[j].send_flag = HCP_SET_PARA_SEND_FLAG_OFF;
            }
            else
            {}
        }
        for(j = 0; j < HCP_PARA_SET_NUM; j++)
        {
            if(HCP_SET_PARA_FLAG_ON == HcpSetPara[j].flag)
            {
                flag ++;
            }
            else
            {}
            if(HCP_SET_PARA_SEND_FLAG_OFF == HcpSetPara[j].send_flag)
            {
                send_flag ++;
            }
            else
            {}
        }
        if(flag == send_flag)
        {
            for(j = 0; j < HCP_PARA_SET_NUM; j++)
            {
                HcpSetPara[j].send_flag = HCP_SET_PARA_SEND_FLAG_ON;
            }
        }
    }
    else
    {}
    /* 更新界面 */
    emit update_window();
}


/*---------------------------------------------------------------------------------------
 函数原型:  void HcpSetPressure(void)
 功    能:  该函数由通信包处理函数HCP_ProcessPacket调用，用于SETPRESSURE命令 设置压力范围
 输入参数:	NA
 输出参数:	NA
 返 回 值:	NA
 注意事项：
---------------------------------------------------------------------------------------*/
void communicationToMCU::HcpSetPressure(unsigned short int range)
{
    HCPCMD_SETPRESSURE pAck;
    memset((unsigned char *)&pAck,0x00,sizeof(HCPACK_ALIVE_CMD));
    pAck.header.pduOffset = HCP_PDUOFFSET;
    pAck.header.type      = ACK_PACKET;
    pAck.header.sn        = HCP_sn;
    pAck.header.len       = sizeof(HCPCMD_SETPRESSURE);
    pAck.header.cmd = CMD_SET_PRESSURE;
    pAck.range = range;
    memcpy(hcp_txBuf,(unsigned char *)&pAck,sizeof(HCPCMD_SETPRESSURE));
    HcpSendPacket(sizeof(HCPCMD_SETPRESSURE));
}


//用于上位机保存出厂设置命令
void communicationToMCU::HcpSetSaveDefault(void)
{
    HCPCMD      header;
    memset((unsigned char *)&header,0x00,sizeof(HCPCMD));
    header.pduOffset = HCP_PDUOFFSET;
    header.type      = ACK_PACKET;
    header.sn        = HCP_sn;
    header.len   = sizeof(HCPCMD);
    header.cmd = CMD_SAVEDEFAULT;
    memcpy(hcp_txBuf,(unsigned char *)&header,sizeof(HCPCMD));
    HcpSendPacket(sizeof(HCPCMD));
}

//处理上位机恢复出厂设置命令
void communicationToMCU::HcpSetRestore(void)
{
    HCPCMD      header;
    memset((unsigned char *)&header,0x00,sizeof(HCPCMD));
    header.pduOffset = HCP_PDUOFFSET;
    header.type      = ACK_PACKET;
    header.sn        = HCP_sn;
    header.len   = sizeof(HCPCMD);
    header.cmd = CMD_RESTORE;
    memcpy(hcp_txBuf,(unsigned char *)&header,sizeof(HCPCMD));
    HcpSendPacket(sizeof(HCPCMD));
}

//设置硬件版本号命令包
void communicationToMCU::HcpSetRestore(unsigned char Hversion[10])
{
    HCPCMD_SETHVER      pCmd;
    memset((unsigned char *)&pCmd,0x00,sizeof(HCPCMD_SETHVER));
    pCmd.header.pduOffset = HCP_PDUOFFSET;
    pCmd.header.type      = ACK_PACKET;
    pCmd.header.sn        = HCP_sn;
    pCmd.header.len   = sizeof(HCPCMD_SETHVER);
    pCmd.header.cmd = CMD_SET_HVERSION;
    memcpy(pCmd.hardwareVer,Hversion,10);
    memcpy(hcp_txBuf,(unsigned char *)&pCmd,sizeof(HCPCMD_SETHVER));
    HcpSendPacket(sizeof(HCPCMD_SETHVER));
}

//设置生产序列号命令包
void communicationToMCU::HcpSetProductSn(unsigned char sn[16])
{
    HCPCMD_SETSN      pCmd;
    memset((unsigned char *)&pCmd,0x00,sizeof(HCPCMD_SETSN));
    pCmd.header.pduOffset = HCP_PDUOFFSET;
    pCmd.header.type      = ACK_PACKET;
    pCmd.header.sn        = HCP_sn;
    pCmd.header.len   = sizeof(HCPCMD_SETSN);
    pCmd.header.cmd = CMD_SET_SN;
    memcpy(pCmd.sn,sn,16);
    memcpy(hcp_txBuf,(unsigned char *)&pCmd,sizeof(HCPCMD_SETSN));
    HcpSendPacket(sizeof(HCPCMD_SETSN));
}

//获取设备信息命令
void communicationToMCU::HcpGetDeviceInfo(void)
{
    HCPCMD head;
    memset((unsigned char *)&head,0x00,sizeof(HCPCMD));
    head.pduOffset = HCP_PDUOFFSET;
    head.type      = ACK_PACKET;
    head.sn        = HCP_sn;
    head.len   = sizeof(HCPCMD);
    head.cmd = CMD_SET_SN;
    memcpy(hcp_txBuf,(unsigned char *)&head,sizeof(HCPCMD));
    HcpSendPacket(sizeof(HCPCMD));
}


//获取设备信息
void communicationToMCU::HcpHandleGetDeviceInfo(unsigned char *puf)
{
    PHCPACK_DEVINFO pAck;
    memset((unsigned char *)&pAck,0x00,sizeof(PHCPACK_DEVINFO));
    pAck = (PHCPACK_DEVINFO)puf;
    if(NULL == pAck)
    {
        return;
    }
    else
    {}
}

// 工作模式：0xaa自动模式；0x55手动模式
void communicationToMCU::HcpSetCmdWordMode(unsigned char WorkMode)
{
     HCPCMD_SETWORKMODE SetPara;
     memset((unsigned char *)&SetPara,0x00,sizeof(HCPCMD_SETWORKMODE));
     SetPara.header.pduOffset = HCP_PDUOFFSET;
     SetPara.header.type = CMD_PACKET;
     SetPara.header.cmd = CMD_SET_WORKMODE;
     SetPara.header.len = sizeof(HCPCMD_SETWORKMODE);
     SetPara.parmID = WorkMode;
     memcpy(hcp_txBuf,(unsigned char *)&SetPara,sizeof(HCPCMD_SETWORKMODE));
     HcpSendPacket(sizeof(HCPCMD_SETWORKMODE));
}

//ProductMode: 0xaa设置总成模式;0x55分离模式
void communicationToMCU::HcpSetCmdProductMode(unsigned char ProductMode)
{
     HCPCMD_SETPRODUCMODE SetPara;
     memset((unsigned char *)&SetPara,0x00,sizeof(HCPCMD_SETPRODUCMODE));
     SetPara.header.pduOffset = HCP_PDUOFFSET;
     SetPara.header.type = CMD_PACKET;
     SetPara.header.cmd = CMD_SET_PRODUCTMODE;
     SetPara.header.len = sizeof(HCPCMD_SETPRODUCMODE);
     SetPara.parmID = ProductMode;
     memcpy(hcp_txBuf,(unsigned char *)&SetPara,sizeof(HCPCMD_SETPRODUCMODE));
     HcpSendPacket(sizeof(HCPCMD_SETPRODUCMODE));
}

/*---------------------------------------------------------------------------------------
 函数原型:  unsigned char *SetCmdPara(void)
 功    能:  参数设置
 输入参数:
 ParaId
 0x00: 测试参数，不区分设备类型
 0xFC: 测试参数，0xFC:代表直压机型
 0xFD: 测试参数，0xFD:代表流量机型
 0xFE: 测试参数，0xFE:代表差压机型
 0x01: 开关量控制，清空参数列表，等待测试参数，复位差压采样数据更新标记
 0x02: 清空参数列表，等待测试参数，立即执行开关量
 0x03: 清空参数列表,复位差压采样数据更新标记
 0xFF: 开关量输出
 输出参数:NA
 返 回 值:发送缓冲区指针
 注意事项：
---------------------------------------------------------------------------------------*/

void communicationToMCU::HcpSetCmdPara( unsigned int DO,unsigned char PFCtaskNum,unsigned char parmID,unsigned int PFCtaskTime)
{
    HCPCMD_SETPARM SetPara;
    memset((unsigned char *)&SetPara,0x00,sizeof(HCPCMD_SETPARM));
    SetPara.header.pduOffset = HCP_PDUOFFSET;
    SetPara.header.type = CMD_PACKET;
    SetPara.header.cmd = CMD_SET_PARM;
    SetPara.header.len = sizeof(HCPCMD_SETPARM);
    SetPara.DO = DO;             //开关量配置值
    SetPara.PFCtaskNum = PFCtaskNum;     //测试节拍编号
    SetPara.parmID = parmID;         //参数配置命令字
    SetPara.PFCtaskTime = PFCtaskTime;    //测试节拍时间
    printf("SetPara.header.pduOffset =%d\n",SetPara.header.pduOffset);
    printf("SetPara.header.type =%d\n",SetPara.header.type);
    printf("SetPara.header.cmd =%d\n",SetPara.header.cmd);
    printf("SetPara.DO =%d\n",SetPara.DO);
    printf("SetPara.PFCtaskNum =%d\n",SetPara.PFCtaskNum);
    printf("SetPara.parmID =%d\n",SetPara.parmID);
    printf("SetPara.PFCtaskTime =%d\n",SetPara.PFCtaskTime);
    memcpy(hcp_txBuf,(unsigned char *)&SetPara,sizeof(HCPCMD_SETPARM));
    HcpSendPacket(sizeof(HCPCMD_SETPARM));
}


//处理按键
void communicationToMCU::HcpHandleKey(unsigned char *puf)
{
    PHCPCMD_SET_KEY pAck;
    pAck = (PHCPCMD_SET_KEY)puf;

    if( NULL == pAck)
    {
        return;
    }
    else
    {}
    if((0xaa == pAck->parmID)
        || (0x55 == pAck->parmID))
    {
        systemData.KeyValue = pAck->parmID;
        printf("systemData.KeyValue =%d\n",systemData.KeyValue );
    }
    else
    {}
}


//处理按键
void communicationToMCU::HcpHandleEvent(unsigned char *puf)
{
    unsigned int data = 0;
    unsigned int mode_a_start = 0;
    unsigned int mode_b_start = 0;
    unsigned char mode_a_hold = 0;
    unsigned char mode_b_hold = 0;
    unsigned char code_select = 0;
    unsigned char code = 0;
    PHCPCMD_SET_COMMON pAck;
    pAck = (PHCPCMD_SET_COMMON)puf;

    if( NULL == pAck)
    {
        return;
    }
    else
    {}
    if(CMD_COMMOM_SET_EVENT == pAck->parmID)
    {
        data = ~(pAck->data) & 0x0000FFFF;
        mode_a_start = (data >> 1) & 0x00000001;
        mode_b_start = (data >> 0) & 0x00000001;
        mode_a_hold  = (data >> 3) & 0x00000001;
        mode_b_hold  = (data >> 4) & 0x00000001;
        code_select = (data >> 5) & 0x00000001;\
        code = ((data >> 5) & 0x00000001) + ((data >> 10) & 0x00000002) \
                + ((data >> 9) & 0x00000004) + ((data >> 8) & 0x00000008) \
                + ((data >> 7) & 0x00000010) + ((data >> 6) & 0x00000020);
        if(1 == (data >> 11) & 0x00000001)
        {
            systemData.KeyValue = 0x55;
        }
        else
        {
            if((BEAT_STATE_STOP == systemData.BeatState)
                && (1 == systemData.args_config.model))
            {
                if((1 == mode_a_start) && (0 == mode_b_start))
                {
                    systemData.KeyValue = 0xaa;
                    if(1 == code_select)
                    {
                        systemData.channel_number = code;
                    }
                    else
                    {}
                    DataInit();
                }
                else if((0 == mode_a_start) && (1 == mode_b_start))
                {
                    systemData.KeyValue = 0xaa;
                    if(1 == code_select)
                    {
                        systemData.channel_number_B = code;
                    }
                    else
                    {}
                    DataInit();
                }
            }
            else
            {
            }
        }
    }
    else
    {}
}

int communicationToMCU::uart_fifo_push(unsigned char data)
{
    if (((data_in+1) % BUF_RXD_SIZE) == data_out)
    {
        return -1;
    }
    else
    {
        buf_rxd[data_in] = data;
        data_in = (data_in+1) % BUF_RXD_SIZE;
        return 0;
    }
}

int communicationToMCU::uart_fifo_pop(unsigned char *data)
{   
    if (data_out == data_in)
    {
        return -1;
    }
    else
    {
        data[0] =   buf_rxd[data_out];
        data_out = (data_out+1) % BUF_RXD_SIZE;
        return 0;
    }
}


void communicationToMCU::HandlePacket(unsigned char *puf)
{
    PHCPCMD pCmd;
    memset((unsigned char *)&pCmd,0x00,sizeof(PHCPCMD));
    pCmd = (PHCPCMD)puf;
    switch(pCmd->cmd)   //命令码分析
    {
        case CMD_HANDSHAKE:
            hcpHandleHandShake(puf);
            break;
        case CMD_SET_PARM:
            break;
        case CMD_SET_PRESSURE:
            break;
        case CMD_SAVEDEFAULT:
            break;
        case CMD_RESTORE:
            break;
        case CMD_SET_HVERSION:
            break;
        case CMD_SET_SN:
            break;
        case CMD_SET_CFGID:
            break;
        case CMD_GET_INFO:
            break;
        case CMD_ENGMODE:
            break;
        case CMD_SET_WORKMODE:
        case CMD_SET_PRODUCTMODE:
            //HCP_SendNACK(0);
            break;
        case CMD_SET_KEY:
            HcpHandleKey(puf);
           break;
        case CMD_SET_COMMON:
            break;
        default:
            //HCP_SendNACK(NACK_WHY_BADCMD);         //无效的命令，否认应答
            break;
    }
 
}
/*---------------------------------------------------------------------------------------
 函数原型:  void HCP_ProcessPacket(void)
 功    能:  判断命令包类型，根据命令字做相应的处理
 输入参数:	NA
 输出参数:	NA
 返 回 值:	NA
 注意事项：
---------------------------------------------------------------------------------------*/
void communicationToMCU::HcpProcessPacket(void)
{
    unsigned short int i = 0;
    unsigned short int data_len = 0;
    unsigned short int data_valid_len = 0;
    unsigned short int tmp = 0;
    unsigned short int tmp_crc = 0;

    if (data_in != data_out)
    {
        data_len = (data_in > data_out) ? (data_in - data_out) : ( data_in + BUF_RXD_SIZE - data_out);
        for(i = 0 ; i < data_len; i++)
        {
            if((HCP_PDUOFFSET == buf_rxd[(data_out + i) % BUF_RXD_SIZE]) && (data_len > 6)
                && ((CMD_PACKET == buf_rxd[(data_out + i + 1) % BUF_RXD_SIZE]) || (ACK_PACKET == buf_rxd[(data_out + i + 1) % BUF_RXD_SIZE])))
            {
                    if((buf_rxd[(data_out + i + 4) % BUF_RXD_SIZE] + 2) <= data_len)
                    {
                            data_valid_len = buf_rxd[(data_out + i + 4) % BUF_RXD_SIZE] + 2;
                            break;
                    }
                    else
                    {}
            }
        }
    }
    else
    {}
    if(data_valid_len > 0)
    {
        memset(data_buf,0x00,BUF_RXD_SIZE);
        for(i = 0; i < data_valid_len ; i++)
        {
            if(0 != uart_fifo_pop(&data_buf[i]))
            {
                break;
            }
            else
            {}
        }
        tmp = (data_buf[data_valid_len - 2] << 8) | data_buf[data_valid_len - 1];
        tmp_crc = crc(data_buf,data_valid_len - 2);     
        if(tmp == tmp_crc)
        {
            HandlePacket(data_buf);
        }
        else
        {}
    }
    else
    {}
}

void communicationToMCU::DataInitPara(unsigned int channel_number,unsigned char parmID,unsigned char num,unsigned char start_index)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int m = 0;
    unsigned int n = 0;
    for(j = 0; j < num; j++)
    {
        m = channel_number / 16;
        n = channel_number % 16;
        for(i = 0; i < BEATS_NUM_MAX; i++)
        {
            if(sets[m][n].time[i] > 0)
            {
                HcpSetPara[start_index + j].ParaSet[i].PFCtaskTime = sets[m][n].time[i] * 1000;//秒（s）转化毫秒（ms）
            }
            else
            {
                HcpSetPara[start_index + j].ParaSet[i].PFCtaskTime = 100;
            }
            if(DIRECT_PRESSURE_PARA == systemData.args_config.test_mode)
            {
                HcpSetPara[start_index + j].ParaSet[i].DO = do_action.direct_type.action[i];
            }
            else
            {
                HcpSetPara[start_index + j].ParaSet[i].DO = do_action.flow_type.action[i];
            }

            HcpSetPara[start_index + j].ParaSet[i].revealStandardUpLimit = sets[m][n].revealStandardUpLimit;//泄露标准上限
            HcpSetPara[start_index + j].ParaSet[i].revealStandardDownLimit = sets[m][n].revealStandardDownLimit;//泄露标准下限
            HcpSetPara[start_index + j].ParaSet[i].revealUnit = sets[m][n].revealUnit;//泄露单位
            HcpSetPara[start_index + j].ParaSet[i].bigRevealStandardValue = sets[m][n].bigRevealStandardValue;//大泄露标准值
            HcpSetPara[start_index + j].ParaSet[i].testPressure = sets[m][n].testPressure;//测试压
            HcpSetPara[start_index + j].ParaSet[i].testPressureBigRevealUint = sets[m][n].testPressureBigRevealUint;//测试压单位
            HcpSetPara[start_index + j].ParaSet[i].testPressureUpLimit = sets[m][n].testPressureUpLimit;//测试压上限
            HcpSetPara[start_index + j].ParaSet[i].testPressureDownLimit = sets[m][n].testPressureDownLimit;//测试压下限
            HcpSetPara[start_index + j].ParaSet[i].measuredVolume = sets[m][n].measuredVolume;//被测试容积/* mL */
            HcpSetPara[start_index + j].ParaSet[i].standerVolume = sets[m][n].standerVolume;//标准物容积/*mL*/
            HcpSetPara[start_index + j].ParaSet[i].markingTime = sets[m][n].markingTime; //打标时长

            HcpSetPara[start_index + j].ParaSet[i].PFCtaskNum = i + 1;
            HcpSetPara[start_index + j].ParaSet[i].parmID = parmID;
        }
        HcpSetPara[start_index + j].flag      = HCP_SET_PARA_FLAG_ON;
        HcpSetPara[start_index + j].send_flag = HCP_SET_PARA_SEND_FLAG_ON;
    }   
}

void communicationToMCU::DataInitMode(unsigned int channel_number,int model,unsigned char parmID)
{
   
    switch(systemData.args_config.test_mode)
    {
      case DIRECT_PRESSURE_PARA:
      case FLOW_TYPE_PARA:
        DataInitPara(channel_number,parmID,1,0);
        break;
      default:
        switch(model)
        {
            case WORKPLACE_MODE_P:
            case WORKPLACE_MODE_N:
              DataInitPara(channel_number,parmID,1,0);
              break;
            case WORKPLACE_MODE_P_N:
            case WORKPLACE_MODE_N_P:
               DataInitPara(channel_number,parmID,2,0);
              break;
            default:
              break;
        }
        break;
    }
}


void communicationToMCU::DataInit(void)
{
    unsigned char parmID = 0;
    switch(systemData.args_config.test_mode)
    {
        case DIRECT_PRESSURE_PARA:
          parmID = 0xFC;
        case FLOW_TYPE_PARA:
          parmID = 0xFD;
          break;
        case DIFF_PRESSURE_PARA:
        default:
          parmID = 0xFE;
          break;
    }
    if(WORKPLACE_A == systemData.args_config.model) //工位A
    {
        DataInitMode(systemData.channel_number,WORKPLACE_A,parmID);
    }
    else if(WORKPLACE_B == systemData.args_config.model) //工位B
    {
         DataInitMode(systemData.channel_number_B,WORKPLACE_B,parmID);
    }
    else if(WORKPLACE_A_AND_B == systemData.args_config.model)//工位A-B
    {
        if(((WORKPLACE_MODE_P == systemData.args_config.A_model)
            && (WORKPLACE_MODE_P == systemData.args_config.B_model))
                || ((WORKPLACE_MODE_P == systemData.args_config.A_model)
                    && (WORKPLACE_MODE_N == systemData.args_config.B_model))
                    || ((WORKPLACE_MODE_N == systemData.args_config.A_model)
                        && (WORKPLACE_MODE_P == systemData.args_config.B_model))
                        || ((WORKPLACE_MODE_N == systemData.args_config.A_model)
                            && (WORKPLACE_MODE_N == systemData.args_config.B_model)))
        {

          DataInitPara(systemData.channel_number,parmID,1,0);
          DataInitPara(systemData.channel_number_B,parmID,1,2);
        }
        else if((((WORKPLACE_MODE_P == systemData.args_config.A_model) || (WORKPLACE_MODE_N == systemData.args_config.A_model))
                && ((WORKPLACE_MODE_P_N == systemData.args_config.B_model)
                    ||(WORKPLACE_MODE_N_P == systemData.args_config.B_model))))
        {
            DataInitPara(systemData.channel_number,parmID,1,0);
            DataInitPara(systemData.channel_number_B,parmID,2,2);           
        }
        else if((((WORKPLACE_MODE_P == systemData.args_config.B_model) || (WORKPLACE_MODE_N == systemData.args_config.B_model))
                && ((WORKPLACE_MODE_P_N == systemData.args_config.A_model)
                    ||(WORKPLACE_MODE_N_P == systemData.args_config.A_model))))
        {
            DataInitPara(systemData.channel_number,parmID,1,2);
            DataInitPara(systemData.channel_number_B,parmID,2,1);
        }
        else
        {
            DataInitPara(systemData.channel_number,parmID,1,2);
            DataInitPara(systemData.channel_number_B,parmID,2,2);    
        }
    }
    else//工位A/B
    {
    }
    systemData.test_press = 0;//测试压
    systemData.press_diff = 0; //差压
    systemData.temp_test_result = 0;
    systemData.set_index = 0;//节拍序号清0
    systemData.KeyValue = 0x00; //手动模式按键值  0xaa开始，0x55停止、0x00初始化
    systemData.BeatState = BEAT_STATE_STOP;
}

unsigned int communicationToMCU::BeatTimerAccm(unsigned int beat_num)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int ret =0;
    for ( i = 0; i < HCP_PARA_SET_NUM; ++i)
    {
        if((HCP_SET_PARA_FLAG_ON == HcpSetPara[i].flag)
            && (HCP_SET_PARA_SEND_FLAG_ING == HcpSetPara[i].send_flag))
        {
            for ( j = 0; j < (beat_num + 1); ++j)
            {
                if(HcpSetPara[i].ParaSet[j].PFCtaskTime > 0)
                {
                    ret += HcpSetPara[i].ParaSet[j].PFCtaskTime;
                }
                else
                {}
            }
        }
        else
        {}
    }
    return ret;
}

void communicationToMCU::beat_do_flag_clear(void)
{
    unsigned int i = 0;
    for ( i = 0; i < BEATS_NUM_MAX; ++i)
    {
        systemData.beat_do_flag[i] = BEAT_DO_FLAG_START;
    }
}

void communicationToMCU::DownloadMode(void)
{
    if(systemData.args_config.model != systemData.args_config.model_prv)
    {
         HcpSetCmdWordMode(systemData.args_config.model);
    }
    else
    {}
}

void communicationToMCU::DownloadProductMode(void)
{
    if(systemData.args_config.product_model != systemData.args_config.product_model_prv)
    {
         HcpSetCmdProductMode(systemData.args_config.product_model);
    }
    else
    {}
}

void communicationToMCU::DownloadTestMode(void)
{
    if(systemData.args_config.test_mode != systemData.args_config.test_mode_prv)
    {
        HcpSetCmdProductMode(systemData.args_config.test_mode);
    }
    else
    {}
}

void communicationToMCU::DownloadSetPara(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int Do = 0;
    unsigned char PFCtaskNum = 0;
    unsigned char parmID = 0;
    unsigned int  PFCtaskTime = 0;

    for(j = 0; j < HCP_PARA_SET_NUM; j++)
    {
        if((HCP_SET_PARA_FLAG_ON == HcpSetPara[j].flag)
            && (HCP_SET_PARA_SEND_FLAG_ON == HcpSetPara[j].send_flag))
        {
            HcpSetPara[j].send_flag = HCP_SET_PARA_SEND_FLAG_ING;
            for(i = 0; i < BEATS_NUM_MAX; i++)
            {
                Do = HcpSetPara[j].ParaSet[i].DO;
                PFCtaskNum = HcpSetPara[j].ParaSet[i].PFCtaskNum;
                parmID = HcpSetPara[j].ParaSet[i].parmID;
                PFCtaskTime = HcpSetPara[j].ParaSet[i].PFCtaskTime;
                HcpSetCmdPara(Do,PFCtaskNum,parmID,PFCtaskTime);
                usleep(20 * 1000);
            }
            break;
        }
        else
        {}
    }
}

void communicationToMCU::CalcTimeTotal(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int time_total = 0;
    for(j = 0; j < HCP_PARA_SET_NUM; j++)
    {
        if((HCP_SET_PARA_FLAG_ON == HcpSetPara[j].flag)
            && (HCP_SET_PARA_SEND_FLAG_ON == HcpSetPara[j].send_flag))
        {
            for(i = 0; i < BEATS_NUM_MAX; i++)
            {
                time_total += HcpSetPara[j].ParaSet[i].PFCtaskTime;
            }
            break;
        }
        else
        {}
    }
    systemData.time_total = time_total;
}


/*
 * 第一步开始执行:
 * 并判断是否是自动模式,再进行握手
 * 公共函数所有类实例化后调用
 */
void communicationToMCU::start_first()
{
    HcpSetCmdWordMode(systemData.args_config.model);
}

/*
 * 定时检查当前处于第几节拍
 *
 */
void communicationToMCU::check_stage()
{
    unsigned char flag = 0x55;
    printf("systemData.BeatState =%d\n",systemData.BeatState);
    if(BEAT_STATE_STOP == systemData.BeatState)
    {
        if(0 == systemData.args_config.model) //自动模式
        {
            flag = 0xaa;
        }
        else if((1 == systemData.args_config.model) //手动模式
                && (0xaa == systemData.KeyValue))
        {
            flag = 0xaa;
            systemData.KeyValue = 0x00;
        }
        else
        {
            flag = 0x55;
        }
        if(flag == 0xaa)
        {
            systemData.BeatState = BEAT_STATE_START;
            systemData.test_press = 0;//测试压
            systemData.press_diff = 0; //差压
            systemData.temp_test_result = 0;
            systemData.set_index = 0;//节拍序号清0
            //0x01: 开关量控制，清空参数列表，等待测试参数，复位差压采样数据更新标记
            //0x02: 清空参数列表，等待测试参数，立即执行开关量
            //0x03: 清空参数列表,复位差压采样数据更新标记
            HcpSetCmdPara(0,0,0x01,0);
            systemData.set_para_end_flag = 0xaa; 
            timer_over->start(1000);
        }
        else
        {}
     }
    else
    {
        if(0x55 == systemData.set_para_end_flag)
        {
            HcpCmdHandShake();
        }
        else
        {}
        if(0x55 == systemData.KeyValue)//按下停止键
        {
            systemData.KeyValue = 0;
            systemData.BeatState = BEAT_STATE_STOP;
            systemData.test_press = 0;//测试压
            systemData.press_diff = 0; //差压
            systemData.temp_test_result = 0;
            systemData.set_index = 0;//节拍序号清0
            systemData.time_remaining = 0;
            systemData.set_para_end_flag = 0xaa; 
        }
        else
        {}
    }
}

/*
 * 再次循环调用
 */
void communicationToMCU::start_again()
{
    beat_do_flag_clear();
    CalcTimeTotal();
    DownloadSetPara();
    systemData.set_para_end_flag = 0x55;
}

void communicationToMCU::receiveInfoScanner()
{
    QByteArray info = serialPort->readAll();

}

