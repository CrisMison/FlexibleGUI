#ifndef __INC_DRIVER_H__
#define __INC_DRIVER_H__

#ifndef CONFIG_DRIVER_OUTPUT_SCREEN
#define DRIVER_SCRREN_MAX      1
#else
#define DRIVER_SCRREN_MAX      CONFIG_DRIVER_OUTPUT_SCREEN
#endif

#define ALIGNMENT_SCREEN_SIZE   8
#endif