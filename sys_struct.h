#ifndef SYS_STRUCT_H
#define SYS_STRUCT_H

//通信缓冲区长度定义
#define HCP_RXBUFLEN            64
#define HCP_TXBUFLEN            256

//命令字定义
#define CMD_SET_PARM            0x10
#define CMD_SET_PRESSURE        0x11
#define CMD_SET_WORKMODE        0x12
#define CMD_SET_PRODUCTMODE     0x13
#define CMD_SET_KEY             0x14

#define CMD_RESTORE             0x21
#define CMD_SAVEDEFAULT         0x2F
#define CMD_READATA             0x41

#define CMD_HANDSHAKE           0x66
#define CMD_SET_HVERSION        0xE0
#define CMD_SET_SN              0xE1
#define CMD_SET_CFGID           0xE2
#define CMD_GET_INFO            0xF0
#define CMD_ENGMODE             0xF1

//基本应答字定义
#define ACK_DATA                0x01        //数据应答包字
#define ACK_ALIVE               0x66        //握手应答字
#define ACK_YESSIR              0x55        //确认应答字
#define ACK_NACK                0xAA        //否认应答字

//否认应答原因--WHY
#define NACK_WHY_BUSY           0x0001      //设备正在执行上一个命令，不能处理当前命令
#define NACK_WHY_ERROR          0x0002      //设备处于故障状态，不能执行命令
#define NACK_WHY_BADCRC         0x0003      //设备收到了命令包，但发现CRC错误
#define NACK_WHY_BADCMD         0x0004      //设备不支持收到的命令字
#define NACK_WHY_NOTREADY       0x0005      //设备没有准备好所请求的数据
#define NACK_WHY_DISABLED       0x0006      //设备当前模式不允许执行该命令
#define NACK_WHY_BADPARM        0x0007      //命令携带的参数不合理

//通信包类型标记
#define CMD_PACKET              0x01        //命令包类型标记
#define ACK_PACKET              0x02        //应答包类型标记

#define HCP_PDUOFFSET           4           //应用层包净载荷偏移量


//保存/恢复出厂设置控制字
#define HCP_SAVEDEFAULT         0x5555
#define HCP_RESTORE             0xAAAA

//本模块所引用的数据字典数据对象ID定义
#define DDID_WATCHDOG2          0x0003

#define DDID_TIMEBASE           0x000C
#define DDID_SAMPLE1            0x0004

#define DDID_CURRSTEP_SAMPLE2   0x0008
#define DDID_LASTSTEP_SAMPLE1   0x0009
#define DDID_LASTSTEP_SAMPLE2   0x000A
#define DDID_LASTSTEP_NUM       0x000B
/*-----------------------------------------------------------------------------
                            数据类型定义
-----------------------------------------------------------------------------*/


//unsigned short int          两个字节
//unsigned char               一个字节

typedef  struct HCPCMD_tag              //命令包头数据结构定义
{
    unsigned char   pduOffset;    //通信包净载荷偏移量
    unsigned char   type;         //通信包类型：CMD_PACKET or ACK_PACKET
    unsigned short int  sn;       //通信包序列号 两个字节
    unsigned char   devAddr;      //RS485地址
    unsigned char   cmd;          //命令字
}HCPCMD,*PHCPCMD;

typedef  struct HCPCMD_SETPARM_tag      //设置参数命令包
{
    HCPCMD      header;
    unsigned int      DO;             //开关量配置值
    unsigned char       PFCtaskNum;     //测试节拍编号
    unsigned char       parmID;         //参数配置命令字
    unsigned int      PFCtaskTime;    //测试节拍时间
}HCPCMD_SETPARM,*PHCPCMD_SETPARM;

typedef struct HCPCMD_SETPRESSURE_tag  //设置工作压力
{
    HCPCMD      header;
    unsigned short int      range;          //工作压力范围
}HCPCMD_SETPRESSURE,*PHCPCMD_SETPRESSURE;

typedef struct HCPCMD_READATA_tag      //读取谱图数据命令包
{
    HCPCMD      header;
    unsigned char       channel;
    unsigned char       count;
    unsigned short int      offset;
}HCPCMD_READATA,*PHCPCMD_READATA;
typedef  struct HCPCMD_SETHVER_tag      //设置硬件版本号命令包
{
    HCPCMD      header;
    unsigned char       hardwareVer[10];
}HCPCMD_SETHVER,*PHCPCMD_SETHVER;

typedef struct HCPCMD_SETSN_tag        //设置生产序列号命令包
{
    HCPCMD      header;
    unsigned char       sn[16];
}HCPCMD_SETSN,*PHCPCMD_SETSN;

typedef struct HCPCMD_SETCFGID_tag     //设置配置ID
{
    HCPCMD      header;
    unsigned char       cfgID[8];
}HCPCMD_SETCFGID,*PHCPCMD_SETCFGID;

typedef struct HCPCMD_ENGMODE_tag      //工程模式命令
{
    HCPCMD      header;
    unsigned char       pwd[16];
}HCPCMD_ENGMODE,*PHCPCMD_ENGMODE;


typedef  struct HCPACK_tag              //应答包头数据结构定义
{
    unsigned char   pduOffset;          //通信包净载荷偏移量
    unsigned char   type;               //通信包类型：CMD_PACKET or ACK_PACKET
    unsigned short int  sn;             //通信包序列号
    unsigned char   devAddr;            //RS485地址
    unsigned char   ack;                //应答字
}HCPACK,*PHCPACK;

typedef struct HCPACK_NACK_tag        //否定应答包头数据结构定义
{
    unsigned char   pduOffset;          //通信包净载荷偏移量
    unsigned char   type;               //通信包类型：CMD_PACKET or ACK_PACKET
    unsigned short int  sn;             //通信包序列号
    unsigned char   devAddr;            //RS485地址
    unsigned char   ack;                //应答字
    unsigned short int  why;            //否定应答原因
}HCPACK_NACK,*PHCPACK_NACK;

typedef struct HCPACK_ALIVE_CMD_tag      //握手应答包
{
    HCPCMD      header;
}HCPACK_ALIVE_CMD,*PHCPACK_ALIVE_CMD;

typedef  struct HCPACK_ALIVE_tag      //握手应答包
{
    HCPACK      header;
    unsigned  int      timeBase;       //测试流程时间基准
    unsigned short int      writePos;       //数据缓冲区(差压)当前写入位置
    unsigned short int      sample1;        //直压采样值
    unsigned short int      currStepSample2;//当前节拍差压采样值
    unsigned short int      lastStepSample1;//上一节拍直压采样值
    unsigned short int      lastStepSample2;//上一节拍差压采样值
    unsigned short int      lastStepNum;    //上一节拍编号
}HCPACK_ALIVE,*PHCPACK_ALIVE;

typedef  struct HCPACK_DATA_tag       //读取谱图数据应答包
{
    HCPACK      header;
    unsigned char       channel;
    unsigned char       count;
    int       data[];

}HCPACK_DATA,*PHCPACK_DATA;

typedef  struct HCPACK_DEVINFO_tag   //获取设备识别信息应答包
{
    HCPACK              header;
    unsigned short int  len;
    unsigned char       venderID[6];
    unsigned char       deviceID[10];
    unsigned char       hardwareVer[10];
    unsigned char       firmwareVer[12];
    unsigned char       cfgID[8];
    unsigned char       sn[16];
}HCPACK_DEVINFO,*PHCPACK_DEVINFO;

typedef struct HCPCMD_SETWORKMODE_tag
{
    HCPCMD              header;
    unsigned char       parmID;
}HCPCMD_SETWORKMODE,*PHCPCMD_SETWORKMODE;

typedef struct HCPCMD_SETPRODUCMODE_tag
{
    HCPCMD              header;
    unsigned char       parmID;
}HCPCMD_SETPRODUCMODE,*PHCPCMD_SETPRODUCMODE;

typedef struct HCPCMD_SET_KEY_tag
{
    HCPCMD              header;
    unsigned char       parmID;
}HCPCMD_SET_KEY,*PHCPCMD_SETK_EY;
#endif
