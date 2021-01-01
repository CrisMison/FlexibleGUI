#ifndef __FG_OUTPUT_H__
#define __FG_OUTPUT_H__

#define FG_ERR(...)  do {printf("[ERR][%s:%d]", __FUNCTION__, __LINE__); printf(__VA_ARGS__); }while(0)
#define FG_INFO(...) do {printf("[INFO][%s:%d]", __FUNCTION__, __LINE__); printf(__VA_ARGS__); }while(0)

#endif