#ifndef __MY_ALLOCATOR_HEADER_
#define __MY_ALLOCATOR_HEADER_

#include <main_header.h>

#define _CHUNK_SIZE_ 64
#define _CALL_SIZE_  256

#ifndef _MEM_SEGMENT_S
#define _MEM_SEGMENT_S
struct mem_segment
{
    void*  ptr_cmp;
    bool   isfree;
    pthread_t tid; 
    struct mem_segment* next;
    size_t size_chunk;
};
typedef struct mem_segment mseg_t;
#endif

extern mseg_t* memory_pool;
extern mseg_t* free_chunck;

extern void* my_mmap(int size);

#endif