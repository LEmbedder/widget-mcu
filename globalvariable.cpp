#include "globalvariable.h"

struct SystemData systemData;
struct SetsPara sets[4][BUTTON_NUMBER];


//机型配置DO动作
do_action_s do_action;
struct HcpSetsPara set_para[4][BEATS_NUM_MAX];

/* 粘贴参数,保存地址使用 */
struct CopyPaste copyPaste;
struct PassWord passWord;

hcp_set_para_s HcpSetPara[HCP_PARA_SET_NUM];

