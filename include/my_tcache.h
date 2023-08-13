#ifndef __MY_TCACHE_HEADER_
#define __MY_TCACHE_HEADER_

#include <main_header.h>

int         calc_tcache_size(void);
void        create_tcache(arena_t* arena, void* addr);
void        maps_run_on_radix_tree(arena_t* arena);
arena_t*    set_arena(void);
// to other header not for tcache only
void        insert_run_on_radix_tree(void* addr);
size_t      arena_size_req();
void        create_arena(void* ptr);

#endif