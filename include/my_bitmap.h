#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>

#define BITMAP_SIZE 32

#ifndef _BITMAP_S_
#define _BITMAP_S_
struct bitmap
{
    int             nb_page;
    struct bitmap*  next;    
    unsigned char   data;
};
typedef struct bitmap bmp_t;
#endif

void    insert_bmp(bmp_t** head, bmp_t* bmp_to_insert);
void    set_bitmap(bmp_t* bmp);
void    set_bit(bmp_t* bmp, int index, int value);
bool    is_bitmap_full(bmp_t* bmp);
void    set_in_bmp(bmp_t* bmp, int index, int value);
void    set_bits(bmp_t* bmp, int start, int len, int value);
void    initialize_bit_list(void* ptr, int nb_page);
int     get_bit(bmp_t bmp, int index);
int     count_free_bits(bmp_t* bmp, int from, int len);
int     find_free_slot(bmp_t* bmp, int len);

#endif