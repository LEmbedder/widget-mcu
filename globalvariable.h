#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QString>
#include "communicationtomcu.h"

#define BUTTON_NUMBER 16

/* 界面参数配置 */
struct Args_config {
    int model;
    int worker_space;
    int A_model;
    int B_model;
    int product_model;
    int test_press_decimal_bit;/* 测试压小数位 */
    int reveal_decimal_bit; /* 泄露值小数位 */
    int test_mode;//测试模式
    /* "容积测试","定标测试" */
        int leak_quantity;//泄露量
        int demarcate_leak;//标定泄露量
        double demarcate_coefficient;//标定系数
    /* "容积测试","定标测试" end*/
    char work_number[30] ;//工号


};

/* 全局变量 */
struct SystemData{
    double test_press;
    double temp_test_result;/* 测试结果 */
    struct Args_config args_config;
    int channel_number;//通道号 1-48
    /* 绘图的上下限 */
    struct Up_down_limit{
        int up_limit;
        int down_limit;
    }up_down_limit;
};

struct SetsPara{
    unsigned int time[13];//测试节拍 单位 s

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
extern SystemData systemData;
extern SetsPara sets[4][BUTTON_NUMBER];
extern CopyPaste copyPaste;
extern communicationToMCU *communication;

#endif // GLOBALVARIABLE_H
