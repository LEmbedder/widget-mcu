#ifndef SYS_STRUCT_H
#define SYS_STRUCT_H

//ͨ�Ż��������ȶ���
#define HCP_RXBUFLEN            64
#define HCP_TXBUFLEN            256

//�����ֶ���
#define CMD_SET_PARM            0x10
#define CMD_SET_PRESSURE        0x11

#define CMD_RESTORE             0x21
#define CMD_SAVEDEFAULT         0x2F
#define CMD_READATA             0x41

#define CMD_HANDSHAKE           0x66
#define CMD_SET_HVERSION        0xE0
#define CMD_SET_SN              0xE1
#define CMD_SET_CFGID           0xE2
#define CMD_GET_INFO            0xF0
#define CMD_ENGMODE             0xF1

//����Ӧ���ֶ���
#define ACK_DATA			    0x01		//����Ӧ�����
#define ACK_ALIVE			    0x66		//����Ӧ����
#define ACK_YESSIR			    0x55		//ȷ��Ӧ����
#define ACK_NACK			    0xAA		//����Ӧ����

//����Ӧ��ԭ��--WHY
#define NACK_WHY_BUSY		    0x0001		//�豸����ִ����һ��������ܴ���ǰ����
#define NACK_WHY_ERROR		    0x0002		//�豸���ڹ���״̬������ִ������
#define NACK_WHY_BADCRC		    0x0003		//�豸�յ����������������CRC����
#define NACK_WHY_BADCMD		    0x0004		//�豸��֧���յ���������
#define NACK_WHY_NOTREADY	    0x0005		//�豸û��׼���������������
#define NACK_WHY_DISABLED       0x0006		//�豸��ǰģʽ������ִ�и�����
#define NACK_WHY_BADPARM	    0x0007		//����Я���Ĳ���������

//ͨ�Ű����ͱ��
#define CMD_PACKET 			    0x01		//��������ͱ��
#define ACK_PACKET 			    0x02		//Ӧ������ͱ��

#define HCP_PDUOFFSET           4           //Ӧ�ò�����غ�ƫ����


//����/�ָ��������ÿ�����
#define HCP_SAVEDEFAULT         0x5555
#define HCP_RESTORE             0xAAAA

//��ģ�������õ������ֵ����ݶ���ID����
#define DDID_WATCHDOG2          0x0003

#define DDID_TIMEBASE           0x000C
#define DDID_SAMPLE1            0x0004

#define DDID_CURRSTEP_SAMPLE2   0x0008
#define DDID_LASTSTEP_SAMPLE1   0x0009
#define DDID_LASTSTEP_SAMPLE2   0x000A
#define DDID_LASTSTEP_NUM       0x000B
/*-----------------------------------------------------------------------------
                            �������Ͷ���
-----------------------------------------------------------------------------*/


//unsigned short int          �����ֽ�
//unsigned char               һ���ֽ�

typedef  struct HCPCMD_tag              //�����ͷ���ݽṹ����
{
    unsigned char   pduOffset;    //ͨ�Ű����غ�ƫ����
    unsigned char   type;         //ͨ�Ű����ͣ�CMD_PACKET or ACK_PACKET
    unsigned short int  sn;       //ͨ�Ű����к� �����ֽ�
    unsigned char   devAddr;      //RS485��ַ
    unsigned char   cmd;          //������
}HCPCMD,*PHCPCMD;

typedef  struct HCPCMD_SETPARM_tag      //���ò��������
{
    HCPCMD      header;
    unsigned int      DO;             //����������ֵ
    unsigned char       PFCtaskNum;     //���Խ��ı��
    unsigned char       parmID;         //��������������
    unsigned int      PFCtaskTime;    //���Խ���ʱ��
}HCPCMD_SETPARM,*PHCPCMD_SETPARM;

typedef struct HCPCMD_SETPRESSURE_tag  //���ù���ѹ��
{
    HCPCMD      header;
    unsigned short int      range;          //����ѹ����Χ
}HCPCMD_SETPRESSURE,*PHCPCMD_SETPRESSURE;

typedef struct HCPCMD_READATA_tag      //��ȡ��ͼ���������
{
    HCPCMD      header;
    unsigned char       channel;
    unsigned char       count;
    unsigned short int      offset;
}HCPCMD_READATA,*PHCPCMD_READATA;
typedef  struct HCPCMD_SETHVER_tag      //����Ӳ���汾�������
{
    HCPCMD      header;
    unsigned char       hardwareVer[10];
}HCPCMD_SETHVER,*PHCPCMD_SETHVER;

typedef struct HCPCMD_SETSN_tag        //�����������к������
{
    HCPCMD      header;
    unsigned char       sn[16];
}HCPCMD_SETSN,*PHCPCMD_SETSN;

typedef struct HCPCMD_SETCFGID_tag     //��������ID
{
    HCPCMD      header;
    unsigned char       cfgID[8];
}HCPCMD_SETCFGID,*PHCPCMD_SETCFGID;

typedef struct HCPCMD_ENGMODE_tag      //����ģʽ����
{
    HCPCMD      header;
    unsigned char       pwd[16];
}HCPCMD_ENGMODE,*PHCPCMD_ENGMODE;


typedef  struct HCPACK_tag              //Ӧ���ͷ���ݽṹ����
{
    unsigned char   pduOffset;          //ͨ�Ű����غ�ƫ����
    unsigned char   type;               //ͨ�Ű����ͣ�CMD_PACKET or ACK_PACKET
    unsigned short int  sn;             //ͨ�Ű����к�
    unsigned char   devAddr;            //RS485��ַ
    unsigned char   ack;                //Ӧ����
}HCPACK,*PHCPACK;

typedef struct HCPACK_NACK_tag        //��Ӧ���ͷ���ݽṹ����
{
    unsigned char   pduOffset;          //ͨ�Ű����غ�ƫ����
    unsigned char   type;               //ͨ�Ű����ͣ�CMD_PACKET or ACK_PACKET
    unsigned short int  sn;             //ͨ�Ű����к�
    unsigned char   devAddr;            //RS485��ַ
    unsigned char   ack;                //Ӧ����
    unsigned short int  why;            //��Ӧ��ԭ��
}HCPACK_NACK,*PHCPACK_NACK;

typedef struct HCPACK_ALIVE_CMD_tag      //����Ӧ���
{
    HCPCMD      header;
}HCPACK_ALIVE_CMD,*PHCPACK_ALIVE_CMD;

typedef  struct HCPACK_ALIVE_tag      //����Ӧ���
{
    HCPACK      header;
    unsigned  int      timeBase;       //��������ʱ���׼
    unsigned short int      writePos;       //���ݻ�����(��ѹ)��ǰд��λ��
    unsigned short int      sample1;        //ֱѹ����ֵ
    unsigned short int      currStepSample2;//��ǰ���Ĳ�ѹ����ֵ
    unsigned short int      lastStepSample1;//��һ����ֱѹ����ֵ
    unsigned short int      lastStepSample2;//��һ���Ĳ�ѹ����ֵ
    unsigned short int      lastStepNum;    //��һ���ı��
}HCPACK_ALIVE,*PHCPACK_ALIVE;

typedef  struct HCPACK_DATA_tag       //��ȡ��ͼ����Ӧ���
{
    HCPACK      header;
    unsigned char       channel;
    unsigned char       count;
    int       data[];

}HCPACK_DATA,*PHCPACK_DATA;

typedef  struct HCPACK_DEVINFO_tag   //��ȡ�豸ʶ����ϢӦ���
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


#endif
