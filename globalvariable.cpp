#include "globalvariable.h"

struct SystemData systemData;
struct SetsPara sets[4][BUTTON_NUMBER];

/* 粘贴参数,保存地址使用 */
struct CopyPaste copyPaste;


communicationToMCU *communication;
