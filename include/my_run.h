#ifndef __MY_RUN_HEADER_
#define __MY_RUN_HEADER_

#include <main_header.h>


#ifndef _RUN_S_
#define _RUN_S_
struct _run_s_
{
    bool    is_locked;
    int     last_known_free_position;
    bmp_t   bmp[BITMAP_SIZE];
    char*   byte;
};
typedef struct _run_s_ run_t;
#endif

void    set_in_bmp(run_t* run, int index, int value);
void    clear_in_bmp(run_t* run, int index);
int     get_from_bmp(run_t* run, int index);
int     find_free_slot(run_t* run, size_t size);
bool    is_bitmap_full(run_t* run);

#endif