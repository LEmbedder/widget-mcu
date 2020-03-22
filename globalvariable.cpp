#include "globalvariable.h"

struct SystemData systemData;
struct SetsPara sets[4][BUTTON_NUMBER];
//0xFC直压机型
struct HcpSetsPara DirectPressurePara[BEATS_NUM_MAX];
//0xFD代表差压机型
struct HcpSetsPara FlowTypePara[BEATS_NUM_MAX];
//0xFE代表差压机型
struct HcpSetsPara DiffPressurePara[BEATS_NUM_MAX];



/* 粘贴参数,保存地址使用 */
struct CopyPaste copyPaste;
struct PassWord passWord;

communicationToMCU *communication;
