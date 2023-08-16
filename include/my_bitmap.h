#ifndef __MY_BITMAP_HEADER_
#define __MY_BITMAP_HEADER_

#include <main_header.h>

#define BITMAP_SIZE 32


#ifndef _BITMAP_S_
#define _BITMAP_S_
struct bitmap
{
    unsigned char data;
};
typedef struct bitmap bmp_t;
#endif


void    set_bit(bmp_t* bmp, int index, int value);
void    clear_bit(bmp_t* bmp, int index);
int     get_bit(bmp_t bmp, int index);
#endif