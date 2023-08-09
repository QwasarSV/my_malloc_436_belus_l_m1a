#include <main_header.h>

arena_t* arena;
int arena_size = 0;

void insert_run_on_radix_tree(void* addr)
{
    printf("inserting address into radix tree : %p\n", addr);
    insert(&arena->root, addr);
}

int calc_tcache_size(void)
{
    int index = 0;
    int jndex = 0;
    int total_size = 0;
    int run_size = 0;
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
    return total_size + 1;
}


void create_tcache(void* addr)
{
    int index = 0;
    int jndex = 0;
    int run_size = 0;
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            arena->_tcache_[index][jndex].address = addr;
            run_size = size_class[index][jndex] * (BITMAP_SIZE * 8) + sizeof(run_t);
            run_t* run = addr;
            run->byte = addr + BITMAP_SIZE + 1;
            addr += run_size;
            jndex += 1;
        }
        jndex = 0;
        index += 1;
    }
}

void maps_run_on_radix_tree()
{
    int index = 0;
    int jndex = 0;
    void* addr = NULL;
    insert_run_on_radix_tree((void*)NULL);
    printf("MAPPING ADDRESS\n\n\n:");
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            addr = arena->_tcache_[index][jndex].address;
            printf("insert sizeclass :%i  on addr : %p\n", size_class[index][jndex], arena->_tcache_[index][jndex].address);
            insert_run_on_radix_tree((void*)addr);
            jndex += 1;
        }
        jndex = 0;
        index += 1;
    }
    printf("MAPPING ADDRESS END...\n\n\n:");
}

void new_run_batch(void)
{   
    int size_arena = sizeof(arena_t);
    arena_size = calc_tcache_size();
    char* memory = my_mmap(arena_size);
    void* run_start = memory + size_arena + 1;
    arena = (arena_t*)memory;
    create_tcache(run_start);
    maps_run_on_radix_tree();
    loop_test_addr_retrieval();
}

