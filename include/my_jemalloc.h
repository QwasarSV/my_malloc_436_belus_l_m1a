#ifndef __MY_JEMALLOC_HEADER_
#define __MY_JEMALLOC_HEADER_

#include <main_header.h>


arena_t*    find_binmap(void* ptr);
int         find_next_size_class(arena_t* arena, int spacing, int class);
int         my_free(void* ptr);
void*       my_malloc(size_t size);
run_t*      set_run(void* ptr, size_t size);
void*       get_mem_chunck(size_t size_req);
void        pool_mem_req(size_t size_req);
run_t*      search_pool(size_t size_class);
int         to_page_size(size_t size);
int         to_size_class(size_t size);
bool        is_within_class_range(size_t size);


//global pool
int     free_global_slot(run_t* run, void* ptr);
void*   create_custom_sized_run(size_t size);
void*   get_slot(run_t* run, size_t size_req);
void*   req_slot_on_global(size_t size);
void*   request_memory(size_t size);
run_t*  create_from_memory(size_t size);
bool    is_class_pool_free(size_t size);
void    free_class_pool(size_t size);
run_t*  request_run_from_pool(int size);
void    release_global_run(run_t* run);
void    release_slot(run_t* run, void* ptr);

#endif