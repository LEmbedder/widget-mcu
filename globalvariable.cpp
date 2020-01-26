#include "globalvariable.h"

GlobalVariable::GlobalVariable(QObject *parent) : QObject(parent)
{
    memset(&systemData,0,sizeof(struct SystemData));

}
