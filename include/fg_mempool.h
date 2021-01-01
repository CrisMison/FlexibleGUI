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

#endif