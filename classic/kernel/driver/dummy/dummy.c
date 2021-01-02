#include "fg_common.h"
#include "fg_driver.h"
#include "fg_mempool.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

static FG_INT32 sg_iDummyFd = 0;

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
                         FG_UINT32 iAMask, FG_UINT32 iRMask, FG_UINT32 iGMask, FG_UINT32 iBMask)
{
    FG_PTR   pFrameBuffer = NULL;
    FG_INT32 iSize = 0;
    FG_INT32 iRet = 0;
    FG_INT32 iLeftSize = 0;

    if(iWidth == 0 || iHeight == 0 || iDepth == 0 || iAMask == 0 || iRMask == 0 || iGMask == 0 || iBMask == 0)
    {
        FG_ERR("Invalida pamaeter\n");
        return (FG_PTR)NULL;
    }
    iSize = iWidth * iHeight * iDepth;

    sg_iDummyFd = open("/tmp/dummy", O_CREAT|O_RDWR, 0777);
    if(sg_iDummyFd < 0)
    {
        FG_ERR("Create dummy framebuffer driver files failed!, errno = %d\n", errno);
        return (FG_PTR)NULL;
    }

    iLeftSize = iSize;

    while(iLeftSize > 0)
    {
        iRet = write(sg_iDummyFd, "0", MIN(iLeftSize, 1024));
        if(iRet != MIN(iLeftSize, 1024))
        {
            FG_ERR("Can't to expand the dummy filesize, iRet = %d\n", iRet);
            close(sg_iDummyFd);
            return (FG_PTR)NULL;
        }

        if(iLeftSize <=0)
        {
            break;
        }
        else
        {
            iLeftSize -= 1024;
        }
    }

    fsync(sg_iDummyFd);

    pFrameBuffer = mmap(0, iSize, PROT_WRITE | PROT_READ, MAP_SHARED, sg_iDummyFd, 0);
    if(!pFrameBuffer)
    {
        FG_ERR("mmap exchange file error\n");
        close(sg_iDummyFd);
        return (FG_PTR)NULL;
    }

    return pFrameBuffer;
}