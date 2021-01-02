#include "fg_common.h"
#include "fg_mempool.h"

MEMPOOL_BASE sg_stMemPool[MEMPOOL_MAX];

/** 
 * Function:    
 *              fg_zalloc
 * Description: 
 *              Allocate memory by POSIX, and memset the context to empty
 * */
static FG_PTR   fg_zalloc(FG_INT32 iSize)
{
    FG_PTR pPtr = malloc(iSize);
    
    if(pPtr)
    {
        memset(pPtr, 0, iSize);
    }

    return pPtr;
}


/** 
 * Function:    
 *              fg_free
 * Description: 
 *              Free memory by POSIX with assign
 * */
static FG_VOID   fg_free(FG_PTR pPtr)
{
    if(pPtr)
    {
        free(pPtr);
    }
}

static FG_INT32 fg_get_list_num(MEMPOOL_BASE* pBase)
{
    MEMPOOL_NODE* pNext = NULL;
    FG_INT32      iNum = 0;
    if(!pBase)
    {
        return FG_ERROR;
    }

    if(pBase->pNodeList == NULL)
    {
        return 0;
    }

    pNext = pBase->pNodeList;
    while(pNext)
    {
        iNum++;
        pNext = pNext->pNextNode;
    }

    return iNum;
}

/** 
 * Function:    
 *              fg_insert_node
 * Description: 
 *              Insert a mempool node to the mempool
 * */
static FG_INT32  fg_insert_node(MEMPOOL_BASE* pBase, MEMPOOL_NODE* pNode)
{
    MEMPOOL_NODE* pNext = NULL;

    if(!pBase || !pNode)
    {
        return FG_ERROR;
    }

    pNext = pBase->pNodeList;
    if(!pNext)
    {
        pBase->pNodeList = pNode;
        return FG_OK;
    }

    /* Loop for find the last node in the single-direction list */
    while(pNext && pNext->pNextNode != NULL)
    {
        pNext = pNext->pNextNode;
    }

    pNext->pNextNode = pNode;
    pNode->pNextNode = NULL;

    return FG_OK;
}

/** 
 * Function:    
 *              fg_unlink_node
 * Description: 
 *              Unlink a mempool node from the mempool
 * */
static MEMPOOL_NODE*  fg_find_node(MEMPOOL_BASE* pBase, FG_PTR pAddr)
{
    MEMPOOL_NODE* pNext = NULL;

    if(!pBase || !pAddr)
    {
        return (MEMPOOL_NODE*)NULL;
    }

    pNext = pBase->pNodeList;

    /* Loop for find the last node in the single-direction list */
    while(pNext && pNext->pBaseAddr != pAddr)
    {
        pNext = pNext->pNextNode;
    }

    if(pNext == NULL)
    {
        return (MEMPOOL_NODE*)NULL;
    }
    else
    {
        return pNext;
    }
}


/** 
 * Function:    
 *              fg_unlink_node
 * Description: 
 *              Unlink a mempool node from the mempool
 * */
static FG_INT32  fg_unlink_node(MEMPOOL_BASE* pBase, MEMPOOL_NODE* pNode)
{
    MEMPOOL_NODE* pNext = NULL;
    MEMPOOL_NODE* pLast = NULL;
    MEMPOOL_NODE* pTemp = NULL;

    if(!pBase || !pNode)
    {
        return FG_ERROR;
    }

    pNext = pBase->pNodeList;
    if(pNext == NULL)
    {
        return FG_ERROR;
    }

    /* Loop for find the last node in the single-direction list */
    while(pNext && pNext != pNode)
    {
        pLast = pNext;
        pNext = pNext->pNextNode;
    }

    if(pLast == NULL && pNext->pNextNode == NULL)
    {
        pBase->pNodeList = NULL;
        return FG_OK;
    }
    else
    {
        if(pLast)
        {
            pLast->pNextNode = pLast->pNextNode->pNextNode;
            return FG_OK;
        }
        else
        {
            pBase->pNodeList = pNext->pNextNode;
            return FG_OK;
        }
        
    }

    return FG_ERROR;
}

/** 
 * Function:    
 *              fg_get_mempool
 * Description: 
 *              Get the mempool by specific memory pool index
 * */
MEMPOOL_BASE* fg_get_mempool(FG_INT32 iPoolIdx)
{
    if(iPoolIdx >= MEMPOOL_MAX)
    {
        FG_ERR("Pool index error, iPoolIdx %d\n", iPoolIdx);
        return (MEMPOOL_BASE*)NULL;
    }

    return &sg_stMemPool[iPoolIdx];
}

/** 
 * Function:    
 *              fg_alloc_memory
 * Description: 
 *              Allocate a memory from the specific memory pool
 * Notice:      
 *              The mempool will be allocated a memory.If the memory pool hasn't enough memory, then the
 *              pool will be truncated automatically.
 * */
FG_PTR   fg_alloc_memory(FG_INT32 iPoolIdx, FG_INT32 iSize)
{
    FG_INT32        iRet = 0;
    FG_INT32        iCalSize = 0;
    FG_INT32        iIncreasement = 0;
    MEMPOOL_NODE*   pNode = NULL;
    
    if(iPoolIdx >= MEMPOOL_MAX || iSize <= 0)
    {
        FG_ERR("Parameter error, iPoolIdx %d, iSize = %d\n", iPoolIdx, iSize);
        return (FG_PTR)NULL;
    }

    iCalSize = ROUNDUP(iSize, MEMPOOL_BLOCK_ALIGN);

    pNode = (MEMPOOL_NODE*)fg_zalloc(sizeof(MEMPOOL_NODE));
    if(!pNode)
    {
        FG_ERR("Can't allocate memory!\n");
        return (FG_PTR)NULL;
    }

    pNode->pBaseAddr = fg_zalloc(iCalSize);
    if(!pNode->pBaseAddr)
    {
        FG_ERR("Can't allocate memory!\n");
        fg_free(pNode);
        return (FG_PTR)NULL;
    }

    pNode->iSize = iCalSize;

    iRet = fg_insert_node(&sg_stMemPool[iPoolIdx], pNode);
    if(iRet != FG_OK)
    {
        FG_ERR("Can't insert memory to the management list!\n");
        fg_free(pNode->pBaseAddr);
        fg_free(pNode);
        return (FG_PTR)NULL;
    }

    sg_stMemPool[iPoolIdx].iTotalSize += iCalSize;
    sg_stMemPool[iPoolIdx].iNodeNum++;

    return pNode->pBaseAddr;
}

/** 
 * Function:    
 *              fg_alloc_memory
 * Description: 
 *              Allocate a memory from the specific memory pool
 * Notice:      
 *              The mempool will be allocated a memory.If the memory pool hasn't enough memory, then the
 *              pool will be truncated automatically.
 * */
FG_INT32   fg_free_memory(FG_INT32 iPoolIdx, FG_PTR pAddr)
{
    FG_INT32        iRet = 0;
    FG_INT32        iIncreasement = 0;
    MEMPOOL_NODE*   pNode = NULL;
    
    if(iPoolIdx >= MEMPOOL_MAX || !pAddr)
    {
        FG_ERR("Parameter error, iPoolIdx %d, pAddr = %p\n", iPoolIdx, pAddr);
        return FG_ERROR;
    }

    pNode = fg_find_node(&sg_stMemPool[iPoolIdx], pAddr);
    if(!pNode)
    {
        FG_ERR("Can't match pointer %p in mempool %d\n", pAddr, iPoolIdx);
        return FG_ERROR;
    }

    iRet = fg_unlink_node(&sg_stMemPool[iPoolIdx], pNode);
    if(iRet != FG_OK)
    {
        FG_ERR("Can't unlink node %p in mempool %d\n", pNode, iPoolIdx);
        return FG_ERROR;
    }

    sg_stMemPool[iPoolIdx].iTotalSize -= pNode->iSize;
    sg_stMemPool[iPoolIdx].iNodeNum--;

    fg_free(pNode->pBaseAddr);
    fg_free(pNode);

    if(fg_get_list_num(&sg_stMemPool[iPoolIdx]) != sg_stMemPool[iPoolIdx].iNodeNum)
    {
        FG_ERR("ERROR!");
        while(FG_TRUE);
    }

    return FG_OK;
}