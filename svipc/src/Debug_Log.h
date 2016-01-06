#ifndef __USE_DEBUG
#define __USE_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



#define DEBUG_LEVEL 3 //cureent max level is 3

#define USE_DEBUG
#ifdef USE_DEBUG

#ifndef DEBUG_ERR
#define DEBUG_ERR(fmt, args...) \
{\
    if(DEBUG_LEVEL>0)\
    printf("\033[46;31m[%s:%d]\033[0m "#fmt" errno=%d, %m\r\n", __func__, __LINE__, ##args, errno, errno);\
}
#endif

#ifndef DEBUG_INFO
#define DEBUG_INFO(fmt, args...) \
{\
    if(DEBUG_LEVEL>1)\
    printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __func__, __LINE__, ##args);\
}
#endif

#ifndef DEBUG_LINE
#define DEBUG_LINE() \
{\
    if(DEBUG_LEVEL>2)printf("[%s:%s] line=%d\r\n",__FILE__, __func__, __LINE__);\
}
#endif

#else
#define DEBUG_LINE()
#define DEBUG_ERR(fmt, ...)
#define DEBUG_INFO(fmt, ...)
#endif

#endif
