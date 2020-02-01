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

extern SystemData systemData;
#endif // GLOBALVARIABLE_H
