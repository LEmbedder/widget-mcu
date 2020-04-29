#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QString>

#define BUTTON_NUMBER    16
#define BEATS_NUM_MAX    13

#define DIRECT_PRESSURE_PARA     0
#define FLOW_TYPE_PARA           1
#define DIFF_PRESSURE_PARA       2

#define BEAT_STATE_START    0xaa
#define BEAT_STATE_STOP     0x55

//工作模式
#define WORK_MODE_MANUAL        0   //手动模式
#define WORK_MODE_AUTO          1   //自动模式
//工位
#define WORKPLACE_A             0   //工位A
#define WORKPLACE_B             1   //工位B
#define WORKPLACE_A_AND_B       2   //工位A-B
#define WORKPLACE_A_OR_B        3   //工位A/B
//工位模式
#define WORKPLACE_MODE_P        0   //正压
#define WORKPLACE_MODE_N        1   //负压
#define WORKPLACE_MODE_P_N      2   //正负压
#define WORKPLACE_MODE_N_P      3   //负正压

#define CHANNEL_MAX_NUM         64 

#define DIFF_PRESSURE_TYPE       4

#define HCP_PARA_SET_NUM         4


#define HCP_SET_PARA_FLAG_ON         0xaa        
#define HCP_SET_PARA_FLAG_OFF        0x55

#define HCP_SET_PARA_SEND_FLAG_ON      0xaa        
#define HCP_SET_PARA_SEND_FLAG_OFF     0x55

#define HCP_SET_PARA_SEND_FLAG_ING     0xff

//测试结果
#define  TEST_PASS 			                 0 //测试通过
#define  TEST_FAILURE_NG_PLUS                1 //NG+
#define  TEST_FAILURE_NG_MINUS               2 //NG-
#define  TEST_FAILURE_BIG_LEAK               3 //大漏
#define  TEST_FAILURE_UPPER_RANGE            4 //超量程上限
#define  TEST_FAILURE_UNDER_RANGE            5 //低量程下限
#define  TEST_FAILURE_PRESS_UPPER_LIMIT      6 //测试压超上限
#define  TEST_FAILURE_PRESS_UNDER_LIMIT      7 //测试压超下限

//测试节拍
//待机
#define  BEAT_STANDBY            0
//延时1
#define  BEAT_DELAY_ONE          1
//延时2
#define  BEAT_DELAY_TWO          2
//延时3
#define  BEAT_DELAY_THREE        3
//充气
#define  BEAT_INFLATABLE         4
//泄压
#define  BEAT_PRESSURE_RELIEF    5
//平衡1
#define  BEAT_BALANCE_ONE        6
//平衡2
#define  BEAT_BALANCE_TWO        7
//测试
#define  BEAT_TEST               8


/* 界面参数配置 */
struct Args_config {
    int model;
    int model_prv;
    int worker_space;
    int A_model;
    int B_model;
    int product_model;
    int product_model_prv;
    int test_press_decimal_bit;/* 测试压小数位 */
    int reveal_decimal_bit; /* 泄露值小数位 */
    int test_mode;//测试模式
    int test_mode_prv;
    /* "容积测试","定标测试" */
    int leak_quantity;//泄露量
    int demarcate_leak;//标定泄露量
    double demarcate_coefficient;//标定系数
    /* "容积测试","定标测试" end*/
    char work_number[30] ;//工号
    char device_number[20];//设备号
};

/* 全局变量 */
struct SystemData{
    double test_press;//测试压
    double press_diff; //差压
    double temp_test_result;/* 测试结果 */
    int    set_index; //当前测试序号
    unsigned int  time_curl;//当前节拍时间  单位ms
    unsigned int  time_base; //当前时间基准，单片机当前节拍计时 单位ms
    int  time_remaining;//当前节拍剩余时间  单位ms
    unsigned int  time_total;//当前所有节拍时间累加
    unsigned int  time_accu; //当前节拍执行累加时间
    unsigned char set_para_end_flag;
    unsigned char beat_do_flag[BEATS_NUM_MAX];
    struct Args_config args_config;
    unsigned int channel_number;//通道号 1-64
    unsigned int channel_number_B;//通道号 1-64
    /* 绘图的上下限 */
    struct Up_down_limit{
        int up_limit;
        int down_limit;
    }up_down_limit;
    unsigned char KeyValue;//手动模式按键值  0xaa开始，0x55停止、0x00初始化
    unsigned char BeatState;
};


struct SetsPara{
    unsigned int time[BEATS_NUM_MAX];//测试节拍 单位 s

    unsigned int revealStandardUpLimit;//泄露标准上限
    unsigned int revealStandardDownLimit;//泄露标准下限
    QString revealUnit;   //泄露单位

    unsigned int bigRevealStandardValue;//大泄露标准值
    unsigned int testPressure;//测试压
    QString testPressureBigRevealUint;//测试压单位

    unsigned int testPressureUpLimit;//测试压上限
    unsigned int testPressureDownLimit;//测试压下限
    double measuredVolume;//被测试容积/* mL */

    double standerVolume;//标准物容积/*mL*/
    unsigned int markingTime; //打标时长

    unsigned int channelNumber;//通道号
    QString channelDescribe;//通道描述
};

struct CopyPaste{
    struct SetsPara *tempSets;
    bool enable;
};


struct HcpSetsPara{
    unsigned int DO;
    unsigned char PFCtaskNum;
    unsigned char parmID;
    unsigned int  PFCtaskTime;

    unsigned int revealStandardUpLimit;//泄露标准上限
    unsigned int revealStandardDownLimit;//泄露标准下限
    QString revealUnit;   //泄露单位

    unsigned int bigRevealStandardValue;//大泄露标准值
    unsigned int testPressure;//测试压
    QString testPressureBigRevealUint;//测试压单位

    unsigned int testPressureUpLimit;//测试压上限
    unsigned int testPressureDownLimit;//测试压下限
    double measuredVolume;//被测试容积/* mL */

    double standerVolume;//标准物容积/*mL*/
    unsigned int markingTime; //打标时长
 };

/*
 * 密码设置
 */
#define SUPERPASSWORD "qweasd"
struct PassWord{
    QString systemPassword;/* 系统密码 */
    QString userPassword;/* 用户密码 */
    int sysOrUser;/* 1:sys ,0:user */
};

typedef struct do_act_st
{
    uint32_t *action;
    uint32_t action_num;
}do_act_s;

typedef struct do_action_st
{
    do_act_s flow_type;
    do_act_s direct_type;
    do_act_s diff_type[DIFF_PRESSURE_TYPE];
}do_action_s;

typedef struct hcp_set_para_st
{
    HcpSetsPara ParaSet[BEATS_NUM_MAX];
    unsigned char send_flag;    //发送完成标志
    unsigned char flag;         //是否数据需要处理
}hcp_set_para_s;

extern SystemData systemData;
extern SetsPara sets[4][BUTTON_NUMBER];
extern CopyPaste copyPaste;
extern PassWord passWord;
extern do_action_s do_action;

extern hcp_set_para_s HcpSetPara[HCP_PARA_SET_NUM];

#endif // GLOBALVARIABLE_H

