#ifndef __MY_ARENA_HEADER_
#define __MY_ARENA_HEADER_

#include <main_header.h>

#ifndef _RUN_ADDR_
#define _RUN_ADDR_
struct _run_addr_s_
{
    void* address;
};
typedef struct _run_addr_s_ addr_t;
#endif


#define RADIX 2
#define BIT_MAX 64

#ifndef _RADIX_NODE_S_
#define _RADIX_NODE_S_
struct radix_node_s
{
    void *ptr;
    struct radix_node_s *left;   //0
    struct radix_node_s *right;  //1
};
typedef struct radix_node_s radix_t;
#endif


#ifndef _ARENA_S_
#define _ARENA_S_
struct _arena_s_
{
    unsigned long tid;
    addr_t _tcache_[SPACING_COUNT -1][9];
    binmap_t binmap;
    bool (*is_free)(int, int, struct binmap_s*);
    int  (*mark_or_free)(int, int, struct binmap_s*);
};
typedef struct _arena_s_ arena_t;
#endif

// extern arena_t* arena;
// extern int arena_size;

#endif