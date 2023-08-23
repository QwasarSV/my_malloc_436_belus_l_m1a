#ifndef __MY_RUN_HEADER_
#define __MY_RUN_HEADER_

#include <main_header.h>


#ifndef _RUN_S_
#define _RUN_S_
struct _run_s_
{
    bmp_t   bmp[BITMAP_SIZE];
    int     size_class;
    bool    is_locked;
    int     last_known_free_position;
    struct _run_s_* next;
    char*   byte;
};
typedef struct _run_s_ run_t;
#endif

void    set_in_bmp(run_t* run, int index, int value);
void    clear_in_bmp(run_t* run, int index);
int     get_from_bmp(run_t* run, int index);
int     find_free_slot(run_t* run);
bool    is_bitmap_full(run_t* run);
bool    is_bitmap_clear(run_t* run);
void    set_bitmap(run_t* run);
#endif