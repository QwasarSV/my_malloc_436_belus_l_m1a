#ifndef __MY_ALLOCATOR_HEADER_
#define __MY_ALLOCATOR_HEADER_

#include <main_header.h>

#ifndef _TEE_S_
#define _TEE_S_
struct tee_s
{
    unsigned char nb_slot;
};
typedef struct tee_s tee_t;
#endif

#ifndef MEM_HANDLER_S
#define MEM_HANDLER_S
struct mem_handler_s
{
	size_t    	cursor;
	size_t    	size_page;
	void*     	memory;
	radix_t*  	search_tree;
	bitlist_t*  head;
};

typedef struct mem_handler_s handler_t; 
#endif

#ifndef _PAGE_S_
#define _PAGE_S_
struct _page_s_
{
    bitlist_t*  bitnode;
    char*   	byte;
};
typedef struct _page_s_ page_t;
#endif

extern handler_t*   handler;
extern void*        my_mmap(int size);

int     to_page_size(size_t size);
int     calc_nb_slot(size_t size, int nb_page);
int     calc_offset(int slot, int nb_page);
void*   get_ptr(size_t size);
void    set_handler(size_t size_page);
void    initialize_handler();
page_t* set_page(void* ptr, int nb_page);
void*   req_memory(size_t size);
void*   my_malloc(size_t size);
void 	release_mem(bitlist_t* node);
int     my_free(void* ptr);

#endif