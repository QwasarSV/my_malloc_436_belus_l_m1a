#ifndef __MY_RADIX_TREE_
#define __MY_RADIX_TREE_

#include <main_header.h>

#ifndef _RADIX_NODE_S_
#define _RADIX_NODE_S_
struct radix_node_s
{
    void*                ptr;
    struct radix_node_s* left;
    struct radix_node_s* right; 
};
typedef struct radix_node_s radix_t;
#endif

radix_t*    fetch_node();
radix_t*    create_node(void* ptr);
void        insert(radix_t** root, void *ptr);
void*       find_page_start(radix_t* root, void* ptr);

extern radix_t* free_chunk;

#endif