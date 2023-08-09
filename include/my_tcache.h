#ifndef __MY_TCACHE_HEADER_
#define __MY_TCACHE_HEADER_

#include <main_header.h>

int     calc_tcache_size(void);
void    create_tcache(void* addr);
void    maps_run_on_radix_tree();
void    new_run_batch(void);
// to other header not for tcache only
void    insert_run_on_radix_tree(void* addr);
#endif