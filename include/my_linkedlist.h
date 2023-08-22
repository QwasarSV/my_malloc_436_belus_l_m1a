#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>


radix_t*    fetch_node();
radix_t*    create_node(void* ptr);
void        insert(radix_t** root, void *ptr);
void*       find_run_start(radix_t * root, void *ptr);
void        release_run_start(radix_t* root, void *ptr);

void        insert_at_head(node_t** head, node_t* node_to_insert);
void        insert_run_at_head(run_t** head, run_t* run_to_insert);
node_t*     create_arena_node(arena_t* arena);

#endif