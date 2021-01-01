#ifndef __FG_TYPEDEF_H__
#define __FG_TYPEDEF_H__


#define FG_CHAR     char
#define FG_INT8     char
#define FG_INT16    short int
#define FG_INT32    int
#define FG_INT64    long long int
#define FG_UINT8    unsigned char
#define FG_UINT16   unsigned short int
#define FG_UINT32   unsigned int
#define FG_UINT64   unsigned long long int
#define FG_VOID     void
#define FG_PTR      void*

typedef enum
{
    FG_OK       =   0,
    FG_ERROR    =   -1,
}FG_RESULT;

#endif