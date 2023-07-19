#ifndef __MY_ALLOCATOR_HEADER_
#define __MY_ALLOCATOR_HEADER_

#include <main_header.h>

#define _CHUNK_SIZE_ 64
#define _CALL_SIZE_   1024

extern void* my_mmap(int size);


#endif