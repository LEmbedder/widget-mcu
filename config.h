#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <stdio.h>

#define __DEBUG__

#ifdef __DEBUG__

#define DEBUG_LOG(fmt, ...)  do{printf("[%s],<%s>,(%d):",__FILE__,__FUNCTION__,__LINE__);\
                                printf(fmt,##__VA_ARGS__);\
                                fflush(stdout);}while(0);

#endif

/* which print machine to use */
#define PRINTF_DEVIDE  "/dev/usb/lp0"

#endif // CONFIG_H
