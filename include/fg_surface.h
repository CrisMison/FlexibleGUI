#ifndef __FG_SURFACE_H__
#define __FG_SURFACE_H__

#include "fg_typedef.h"

typedef struct
{
    FG_UINT32    iWidth;
    FG_UINT32    iHeight;
    FG_UINT32    iDepth;
    FG_UINT32    iAMask;
    FG_UINT32    iRMask;
    FG_UINT32    iGMask;
    FG_UINT32    iBMask;
    FG_PTR       pVoBuff;
}SURFACE_OUTPUT_BUFFER_PARAM;

/** 
 * Function:    
 *              fg_driver_register_output_screen
 * Description: 
 *              Register the output screen parameter
 *              Driver should be initialized before call this function
 * */
FG_INT32 fg_driver_register_output_screen(FG_INT32 iScreenIdx, SURFACE_OUTPUT_BUFFER_PARAM* pParam);


#endif