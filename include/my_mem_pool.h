#ifndef __MY_MEM_POOL_HEADER_
#define __MY_MEM_POOL_HEADER_

#include <main_header.h>

void init_memory_segment(void* mem_seg, size_t elem_cnt);
radix_t* allocate_node();
void    destroy_memory_pool();
radix_t* fetch_node();

#endif