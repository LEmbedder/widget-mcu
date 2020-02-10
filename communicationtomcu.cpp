#include "sys_struct.h"
#include "communicationtomcu.h"
#include "globalvariable.h"


#define HCP_PDUOFFSET         4     //应用层包净载荷偏移量

//0xaa 收到命令回复
//0x55 收到命令没有回复，或者是回复命令不支持
unsigned char send_flag = 0x55;

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

static unsigned char hcp_rxBuf[HCP_RXBUFLEN];     //uart通信接口接收缓冲区
static unsigned char hcp_txBuf[HCP_TXBUFLEN];     //uart通信接口发送缓冲区

unsigned char hcp_rxBuf_len = 0;    //接收长度
unsigned char hcp_txBuf_len = 0;    //发送长度

unsigned short int HCP_sn = 0;

communicationToMCU::communicationToMCU(QObject *parent) : QObject(parent)
{
    initSerialPort();

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
    hcp_rxBuf_len = info.length();
    qDebug("hcp_rxBuf_len = %d",hcp_rxBuf_len);
    for(int i = 0; i < info.length(); i++)
        qDebug("tmp[%d] = 0x%02x",i,tmp[i]);
    memset(hcp_rxBuf,0x00,HCP_TXBUFLEN);
    memcpy(hcp_rxBuf,tmp,hcp_rxBuf_len);
    HcpProcessPacket();
}

void communicationToMCU::SendToMcu(const char *data, qint64 len)
{
    serialPortToMCU->write(data,len);
}


/*---------------------------------------------------------------------------------------
 函数原型:  unsigned char *HCP_GetRxBuf(void)
 功    能:  根据当前通信端口（HCP_host）获取该通信端口接收缓冲区地址
 输入参数:  NA
 输出参数:  NA
 返 回 值: 接收缓冲区指针
 注意事项：  
---------------------------------------------------------------------------------------*/
unsigned char *communicationToMCU::HcpGetRxBuf(void)
{
    unsigned char *pRxBuf = NULL;
    pRxBuf = hcp_rxBuf;
    return pRxBuf;
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
    pAck->devAddr = 0x00;
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
    pAck->devAddr = 0x00;
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
    printf("length =%d\n",length);
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
    pAck.header.devAddr   = 0l;
    pAck.header.cmd = CMD_HANDSHAKE;
    memcpy(hcp_txBuf,(unsigned char *)&pAck,sizeof(HCPACK_ALIVE_CMD));
    HcpSendPacket(sizeof(HCPACK_ALIVE_CMD));
}

//处理应答包
void communicationToMCU::hcpHandleHandShake(void)
{
    PHCPACK_ALIVE pAck;
    pAck = (PHCPACK_ALIVE)HcpGetTxBuf();

    if( NULL == pAck)
    {
        return;
    }
    else
    {}

    systemData.test_press = pAck->sample1;        //直压采样值
    systemData.press_diff = pAck->currStepSample2;//当前节拍差压采样值
    systemData.set_index = pAck->lastStepNum + 1; //节拍编号
    /*
    pAck->timeBase; //测试流程时间基准
    pAck->writePos; //数据缓冲区(差压)当前写入位置

    pAck->sample1;  //直压采样值
    pAck->currStepSample2; //当前节拍差压采样值

    pAck->lastStepSample1;//上一节拍直压采样值
    pAck->lastStepSample2;//上一节拍差压采样值

    pAck->lastStepNum; //上一节拍编号
    */
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
    pAck.header.devAddr   = 0l;
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
    header.devAddr   = 0l;
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
    header.devAddr   = 0l;
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
    pCmd.header.devAddr   = 0;
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
    pCmd.header.devAddr   = 0l;
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
    head.devAddr   = 0l;
    head.cmd = CMD_SET_SN;
    memcpy(hcp_txBuf,(unsigned char *)&head,sizeof(HCPCMD));
    HcpSendPacket(sizeof(HCPCMD));
}


//获取设备信息
void communicationToMCU::HcpHandleGetDeviceInfo(void)
{
    PHCPACK_DEVINFO pAck;
    memset((unsigned char *)&pAck,0x00,sizeof(PHCPACK_DEVINFO));
    pAck = (PHCPACK_DEVINFO)HcpGetRxBuf();
    if(NULL == pAck)
    {
        return;
    }
    else
    {}
//    pAck->venderID;
//    pAck->deviceID;
//    pAck->hardwareVer;
//    pAck->firmwareVer;
//    pAck->sn;
//    pAck->cfgID;
}

// 工作模式：0xaa自动模式；0x55手动模式
void communicationToMCU::HcpSetCmdWordMode(unsigned char WorkMode)
{
     HCPCMD_SETWORKMODE SetPara;
     memset((unsigned char *)&SetPara,0x00,sizeof(HCPCMD_SETWORKMODE));
     SetPara.header.pduOffset = HCP_PDUOFFSET;
     SetPara.header.type = CMD_PACKET;
     SetPara.header.cmd = CMD_SET_WORKMODE;
     SetPara.parmID = WorkMode;
     memcpy(hcp_txBuf,(unsigned char *)&SetPara,sizeof(HCPCMD_SETWORKMODE));
     HcpSendPacket(sizeof(HCPCMD_SETWORKMODE));
}

//ProductMode: 0xaa设置总成模式;0x55分离模式
void communicationToMCU::HcpSetCmdProductMode(unsigned char ProductMode)
{
     HCPCMD_SETPRODUCMODE SetPara;
     memset((unsigned char *)&SetPara,0x00,sizeof(HCPCMD_SETPRODUCMODE));
     SetPara.header.type = CMD_PACKET;
     SetPara.header.cmd = CMD_SET_PRODUCTMODE;
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
     SetPara.header.type = CMD_PACKET;
     SetPara.header.cmd = CMD_SET_PARM;
     SetPara.DO = DO;             //开关量配置值
     SetPara.PFCtaskNum = PFCtaskNum;     //测试节拍编号
     SetPara.parmID = parmID;         //参数配置命令字
     SetPara.PFCtaskTime = PFCtaskTime;    //测试节拍时间
     printf("len = %d\n",sizeof(HCPCMD_SETPARM));
     memcpy(hcp_txBuf,(unsigned char *)&SetPara,sizeof(HCPCMD_SETPARM));
     HcpSendPacket(sizeof(HCPCMD_SETPARM));
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
    unsigned char  *pRxPacket = NULL;
    PHCPCMD pCmd ;
    memset((unsigned char *)&pCmd,0x00,sizeof(PHCPCMD));
    unsigned short int tmp = 0;
    unsigned short int tmpU16 = 0;
    unsigned short int packetLen = 0;
    //获取命令包缓冲区首地址
    packetLen = hcp_rxBuf_len;
    if( packetLen < sizeof(HCPCMD) + 2)
    {
        return;
    }
    else
    {}
    pRxPacket = hcp_rxBuf;
    //从包缓冲区中取出CRC校验码字段
    tmpU16 = pRxPacket[ packetLen - 2 ];
    tmpU16 = tmpU16 << 8;
    tmpU16 |= pRxPacket[ packetLen - 1 ];
    tmp = crc(pRxPacket, packetLen - 2 );		//计算CRC值
    if(tmp != tmpU16 )  //CRC校验失败
    {
        HCP_SendNACK(NACK_WHY_BADCRC);
        return;
    }
    else
    {}
    pCmd = (PHCPCMD)pRxPacket;
    switch(pCmd->cmd)   //命令码分析
    {
        case CMD_HANDSHAKE:
            hcpHandleHandShake();
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
            HCP_SendNACK(0);
        break;
        default:
            HCP_SendNACK(NACK_WHY_BADCMD);		 	//无效的命令，否认应答
            break;
    }
  }
