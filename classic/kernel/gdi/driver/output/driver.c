#include "fg_common.h"
#include "fg_driver.h"
#include "fg_mempool.h"
#include "inc_driver.h"

static DRIVER_OUTPUT_BUFFER_PARAM sg_stOutputDriver[DRIVER_SCRREN_MAX];

/** 
 * Function:    
 *              fg_driver_register_output_screen
 * Description: 
 *              Register the output screen parameter
 *              Driver should be initialized before call this function
 * */
FG_INT32 fg_driver_register_output_screen(FG_INT32 iScreenIdx, DRIVER_OUTPUT_BUFFER_PARAM* pParam)
{
    FG_INT32 iSize = 0;
    FG_PTR   pBuffer = NULL;

    if(!pParam)
    {
        FG_ERR("Invalid Parameter\n");
        return FG_ERROR;
    }

    if(iScreenIdx >= DRIVER_SCRREN_MAX)
    {
        FG_ERR("Invalid screen idx,  iScreenIdx = %d, limit = %d\n", iScreenIdx, DRIVER_SCRREN_MAX);
        return FG_ERROR;
    }

    if(pParam->iWidth % ALIGNMENT_SCREEN_SIZE != 0 ||
       pParam->iHeight % ALIGNMENT_SCREEN_SIZE != 0)
    {
        FG_ERR("The width or height of the screen must be aligned by %d\n", ALIGNMENT_SCREEN_SIZE);
        return FG_ERROR;
    }

    if(!pParam->pVoBuff)
    {
        FG_ERR("VO Buffer of the screen is invalid\n");
        return FG_ERROR;
    }

    iSize = pParam->iWidth * pParam->iHeight * pParam->iDepth;
    
    /* Test the vo buffer that whether it can be read or written or not */
    pBuffer = fg_alloc_memory(MEMPOOL_DRIVER, iSize);
    if(!pBuffer)
    {
        FG_ERR("Out of memory!\n");
        return FG_ERROR;
    }

    memcpy(pBuffer, pParam->pVoBuff, iSize);
    memcpy(pParam->pVoBuff, pBuffer, iSize);

    fg_free_memory(MEMPOOL_DRIVER, pBuffer);

    memcpy(&sg_stOutputDriver[iScreenIdx], pParam, sizeof(DRIVER_OUTPUT_BUFFER_PARAM));

    return FG_OK;
}