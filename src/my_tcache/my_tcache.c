#include <main_header.h>

// arena_t* arena;
// int arena_size = 0;
size_t mem_call_size;
void insert_run_on_radix_tree(void* addr)
{
    printf("inserting address into radix tree : %p\n", addr);
    insert(&handler->root, addr);
}

int calc_tcache_size(void)
{
    int index = 0;
    int jndex = 0;
    int total_size = 0;
    int run_size = 0;
    long page_size = sysconf(_SC_PAGESIZE);
    total_size += sizeof(arena_t);
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            run_size = size_class[index][jndex] * (BITMAP_SIZE * 8) + sizeof(run_t);
            total_size += run_size;
            jndex += 1;
        }
        jndex = 0;
        index += 1;
    }
    mem_call_size = total_size + (page_size - total_size % page_size);
    return total_size;
}


void create_tcache(arena_t* arena, void* addr)
{
    int index = 0;
    int jndex = 0;
    int run_size = 0;
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            arena->_tcache_[index][jndex].address = addr;
            free_size_class(index, jndex, &arena->binmap);
            run_size = size_class[index][jndex] * (BITMAP_SIZE * 8) + sizeof(run_t);
            run_t* run = addr;
            run->size_class = size_class[index][jndex];
            run->byte = addr + BITMAP_SIZE + 1;
            addr += run_size;
            jndex += 1;
        }
        jndex = 0;
        index += 1;
    }
}

void maps_run_on_radix_tree(arena_t* arena)
{
    int index = 0;
    int jndex = 0;
    void* addr = NULL;
    insert_run_on_radix_tree((void*)NULL);
    // insert_run_on_radix_tree((void*)0xFFFFFFFFFFFFFFFF);
    // printf("MAPPING ADDRESS\n\n\n:");
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            addr = arena->_tcache_[index][jndex].address;
            // printf("insert sizeclass :%i  on addr : %p\n", size_class[index][jndex], arena->_tcache_[index][jndex].address);
            insert_run_on_radix_tree((void*)addr);
            jndex += 1;
        }
        jndex = 0;
        index += 1;
    }
    // printf("MAPPING ADDRESS END...\n\n\n:");
}

size_t arena_size_req()
{
    size_t size_arena_s    = sizeof(arena_t);
    size_t tcache_size     = calc_tcache_size();
    size_t size_req        = size_arena_s + tcache_size;
    return size_req;
}

void create_arena(void* ptr)
{
    size_t   size_arena_s               = sizeof(arena_t);
    handler->arenas_list->arena         = (arena_t*)ptr;
    handler->arenas_list->arena->tid    = (unsigned long)pthread_self();
    void*    run_start                  = ptr + size_arena_s + 1;
    create_tcache(handler->arenas_list->arena, run_start);
    maps_run_on_radix_tree(handler->arenas_list->arena);
    // // test function:
    // loop_test_addr_retrieval(handler->arenas_list->arena);
    // // end test function
}

// arena_t* set_arena(void)
// {
//     size_t size_req = arena_size_req();
//     char* memory = my_mmap(size_req);
//     // arena_t* arena = create_arena(memory);
//     return arena;
// }