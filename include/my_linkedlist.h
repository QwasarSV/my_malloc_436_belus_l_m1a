#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>


radix_t*    fetch_node();
radix_t*    create_node(void* ptr);
void        insert(radix_t** root, void *ptr);
void*       find_run_start(radix_t * root, void *ptr);
radix_t*    fetch_node();

#endif