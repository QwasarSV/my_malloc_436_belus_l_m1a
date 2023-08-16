#ifndef __MY_ALLOCATOR_HEADER_
#define __MY_ALLOCATOR_HEADER_
#include <main_header.h>

#ifndef _NODE_S_
#define _NODE_S_
struct node_s
{
    arena_t* arena;
    struct node_s* next;
};
typedef struct node_s node_t;
#endif

// to merge with void* member node/
#ifndef _NODE_S_
#define _NODE_S_
struct run_node_s
{
    run_t* run;
    size_t size_class;
    struct node_s* next;
};
typedef struct node_s run_node_t;
#endif

#ifndef _GLOBAL_POOL_
#define _GLOBAL_POOL_
struct global_pool
{
    node_t*     arenas_list;
    radix_t*    root;
    run_t*      pool;
    binmap_t    binmap;
    void*       memory;
    int         mem_pos;
};
typedef struct global_pool g_pool_t;
#endif

extern size_t mem_call_size;

extern g_pool_t* handler;
extern void* my_mmap(int size);

void        create_mem_handler(void);
void*       req_mem_for_handler();
size_t      handler_size_req();
arena_t*    find_arena();
#endif