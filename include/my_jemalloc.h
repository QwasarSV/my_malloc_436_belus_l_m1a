#ifndef __MY_JEMALLOC_HEADER_
#define __MY_JEMALLOC_HEADER_

#include <main_header.h>

int     my_free(void* ptr);
void*   req_slot(size_t size);
void*   my_malloc(size_t size);
#endif