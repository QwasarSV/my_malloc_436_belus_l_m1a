#ifndef __MY_BINMAP_HEADER_
#define __MY_BINMAP_HEADER_

#include <main_header.h>


// extern bool binmap[SPACING_COUNT][9];
#define SIZE_FN_PTR 2

#ifndef _BINMAP_S_
#define _BINMAP_S_
struct binmap_s
{
    bool data[SPACING_COUNT][9];
};
typedef struct binmap_s binmap_t;
#endif



bool    is_size_class_free(int spacing, int size_class_index, binmap_t* binmap);
int     mark_size_class(int spacing, int size_class_index, binmap_t* binmap);
int     free_size_class(int spacing, int size_class_index, binmap_t* binmap);


#endif