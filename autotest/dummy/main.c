#include "fg_common.h"
#include "fg_mempool.h"
#include "fg_surface.h"
#include "fg_driver.h"

FG_INT32 main(FG_INT32 iArgs, FG_CHAR* sArgc[])
{
    FG_PTR pFrameBuffer = NULL;

    pFrameBuffer = driver_dummy_init(1024, 768, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    if(pFrameBuffer == NULL)
    {
        FG_ERR("driver_dummy_init failed");
        goto fail;
    }

    memset(pFrameBuffer, 0x80, 1024* 768 * 32);

fail:
    return FG_ERROR;
}
