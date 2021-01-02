#include "fg_common.h"
#include "fg_mempool.h"

#define MAX_ARRAY_SIZE  1024
#define MAX_SIZE        64 * 1024
FG_INT32 main(FG_INT32 iArgs, FG_CHAR* sArgc[])
{
    FG_PTR      pPointer    [MAX_ARRAY_SIZE] = {NULL};
    FG_BOOL     bAllocate   [MAX_ARRAY_SIZE] = {FG_FALSE};
    FG_INT32    iIdx = 0;
    FG_INT32    iSize = 0;
    FG_INT32    iRet = 0;
    FG_INT32    iCnt = 1024;

    if(iArgs > 1)
    {
        if(atoi(sArgc[1]) > 0)
        {
            iCnt = atoi(sArgc[1]);
        }
    }

    for(;iCnt >= 0; iCnt--)
    {
        iIdx  = random() % MAX_ARRAY_SIZE;
        iSize = random() % MAX_SIZE;

        if(bAllocate[iIdx] == FG_FALSE)
        {
            pPointer[iIdx] = fg_alloc_memory(MEMPOOL_WINDOW, iSize);
            if(!pPointer)
            {
                FG_ERR("Testing failed: Allocated: iIdx = %d, iSize = %d\n", iIdx, iSize);
                goto fail;
            }
            
            bAllocate[iIdx] = FG_TRUE;
        }
        else
        {
            iRet = fg_free_memory(MEMPOOL_WINDOW, pPointer[iIdx]);
            if(iRet != FG_OK)
            {
                FG_ERR("Testing failed: Free: pPointer = %p\n", pPointer[iIdx]);
                goto fail;
            }

            pPointer[iIdx] = NULL;
            bAllocate[iIdx] = FG_FALSE;
        }
    }

fail:
    FG_ERR("Testing Program will be halt for debug\n");
    while(FG_TRUE);
    return -1;
ok:
    return 0;
}
