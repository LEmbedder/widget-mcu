#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

/* 界面参数配置 */
struct Args_config {
    int model;
    int worker_space;
    int A_model;
    int B_model;
    int product_model;
};

/* 全局变量 */
struct SystemData{

    struct Args_config args_config;
    int channel_number;//通道号 1-48
};

extern SystemData systemData;
#endif // GLOBALVARIABLE_H
