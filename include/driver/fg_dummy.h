#ifndef __FG_DUMMY_H__
#define __FG_DUMMY_H__

#include "fg_typedef.h"

/** 
 * Function:    
 *              driver_dummy_init
 * Description: 
 *              Initialize the dummy display driver
 *              
 *              Dummy driver use a exchanged-memory file at /tmp/dummy, for exchange the display 
 *              framebuffer with a dummy monitor process
 * 
 *              For more information, check the dummy part of documents.
 * */
FG_PTR driver_dummy_init(FG_UINT32 iWidth, FG_UINT32 iHeight, FG_UINT32 iDepth, 
                         FG_UINT32 iAMask, FG_UINT32 iRMask, FG_UINT32 iGMask, FG_UINT32 iBMask);

#endif