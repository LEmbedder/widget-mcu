#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <stdio.h>

//#define __DEBUG__

#ifdef __DEBUG__

#define DEBUG_LOG(fmt, ...)  do{printf("[%s],<%s>,(%d):",__FILE__,__FUNCTION__,__LINE__);\
                                printf(fmt,##__VA_ARGS__);\
                                fflush(stdout);}while(0);
#define printf(fmt, ...) do{printf(fmt,##__VA_ARGS__)}while(0)
#else
#define printf(fmt, ...)
#define DEBUG_LOG(fmt, ...)
#endif


/* which print machine to use */
#define PRINTF_DEVIDE  "/dev/usb/lp0"

#define MAX_DB_RECORD  100000
#endif // CONFIG_H
