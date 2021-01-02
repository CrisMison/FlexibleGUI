#ifndef __FG_COMMON_H__
#define __FG_COMMON_H__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "fg_typedef.h"
#include "fg_output.h"

#ifndef ROUNDUP
#define ROUNDUP(x, align)    (((x) + align - 1) & ~(align  - 1))
#endif

#ifndef MAX
#define MAX(a,b)    (a>b?a:b)
#endif

#ifndef MIN
#define MIN(a,b)    (a<b?a:b)
#endif

#endif