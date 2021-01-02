#ifndef __FG_DRIVER_H__
#define __FG_DRIVER_H__

#include "fg_typedef.h"

typedef struct
{
    FG_INT32    iWidth;
    FG_INT32    iHeight;
    FG_INT32    iDepth;
    FG_INT32    iAMask;
    FG_INT32    iRMask;
    FG_INT32    iGMask;
    FG_INT32    iBMask;
    FG_PTR      pVoBuff;
}DRIVER_OUTPUT_BUFFER_PARAM;

#endif