#ifndef __FG_MEMPOOL_H__
#define __FG_MEMPOOL_H__

#define MEMPOOL_BLOCK_ALIGN 16

/**
 * Mempool use a single-direction list to manage the memory in the GUI.
 * */
typedef struct _MEMPOOL_NODE
{
    FG_PTR                  pBaseAddr;
    FG_INT32                iSize;
    struct _MEMPOOL_NODE*   pNextNode;
}MEMPOOL_NODE;


typedef struct _MEMPOOL_BASE
{
    FG_INT32        iTotalSize;
    FG_INT32        iNodeNum;
    MEMPOOL_NODE*   pNodeList;
}MEMPOOL_BASE;

typedef enum
{
    MEMPOOL_WINDOW,
    MEMPOOL_MAX,
}MEMPOOL_TYPE_IDX;

/** 
 * Function:    
 *              fg_get_mempool
 * Description: 
 *              Get the mempool by specific memory pool index
 * */
MEMPOOL_BASE* fg_get_mempool(FG_INT32 iPoolIdx);
/** 
 * Function:    
 *              fg_alloc_memory
 * Description: 
 *              Allocate a memory from the specific memory pool
 * Notice:      
 *              The mempool will be allocated a memory.If the memory pool hasn't enough memory, then the
 *              pool will be truncated automatically.
 * */
FG_PTR   fg_alloc_memory(FG_INT32 iPoolIdx, FG_INT32 iSize);

/** 
 * Function:    
 *              fg_alloc_memory
 * Description: 
 *              Allocate a memory from the specific memory pool
 * Notice:      
 *              The mempool will be allocated a memory.If the memory pool hasn't enough memory, then the
 *              pool will be truncated automatically.
 * */
FG_INT32   fg_free_memory(FG_INT32 iPoolIdx, FG_PTR pAddr);

#endif