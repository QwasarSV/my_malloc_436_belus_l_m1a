#include <main_header.h>

int my_free(void* ptr)
{
    int slot = 0;
    run_t* run;
    clear_in_bmp(run, slot);
    run->last_known_free_position = slot;
    return EXIT_SUCCESS;
}

int find_next_size_class(arena_t* arena, int spacing, int class)
{
    int run_req = size_class[spacing][class];
    run_req *=  BITMAP_SIZE * 8;
    while (spacing < SPACING_COUNT -1)
    {
        while (size_class[spacing][class] != 0)
        {
            if (is_size_class_free(spacing, class, &arena->binmap) &&
            size_class[spacing][class] >= run_req)
            {
                return size_class[spacing][class];
            }
            class += 1;
        }
        class = 0;
        spacing += 1;
    }
    return -1;
}

run_t* search_pool(size_t size_class)
{
    run_t* run = handler->pool;
    while (run != NULL)
    {
        if (run->size_class == size_class)
        {
            return run;
        }
        run = run->next;
    }
    return NULL;
}

void pool_mem_req(size_t size_req)
{
    int left_over = mem_call_size - handler->mem_pos;
    if (handler->memory == NULL && left_over <= size_req)
    {
        handler->memory = my_mmap(mem_call_size);
    }
    else if ((handler->memory != NULL && left_over <= size_req))
    {
        munmap(handler->memory, size_req);
        handler->memory = my_mmap(mem_call_size);
    }
}

run_t* create_new_run(arena_t* arena, int spacing, int class)
{
    int size_req = find_next_size_class(arena, spacing, class);
    void* ptr = NULL;

    if (size_req == -1)
    {
        pool_mem_req(size_class[spacing][class]);
        insert_run_on_radix_tree(handler->memory);
        ptr = handler->memory;
        int offset = sizeof(run_t) + (size_class[spacing][class] * BITMAP_SIZE * 8);
        handler->memory = (void*)handler->memory + offset;
        handler->mem_pos += offset;
    }
    else 
    {
        ptr = req_slot(size_req);
        insert_run_on_radix_tree(ptr);
    }
    run_t* run = ptr;
    run->last_known_free_position = 0;
    run->size_class = size_class[spacing][class];
    run->byte = ptr + BITMAP_SIZE + 1;
    run->next = NULL;
    // set_bitmap(run);
    insert_run_at_head(&handler->pool, run);
    free_size_class(spacing, class, &handler->binmap);
    int result = is_size_class_free(spacing, class, &handler->binmap);
    return run;
}

run_t* get_or_create_run(arena_t* arena, int spacing, int class)
{
    run_t* run = NULL;
    int size_req = size_class[spacing][class];   
    if (is_size_class_free(spacing, class, &handler->binmap))
    {
        run = search_pool(size_req);
    }
    else
    {
        run = create_new_run(arena, spacing, class);
    }
    return run;
}

void* req_slot(size_t size)
{
    run_t* run = NULL;
    arena_t* arena = find_arena();
    int spacing = nearest_spacing_index(size);
    int class = get_size_class_index(spacing, size);
    int size_req = size_class[spacing][class];
    void* ptr = NULL;
    if (!is_size_class_free(spacing, class, &arena->binmap))
    {
        run = get_or_create_run(arena, spacing, class);
    }
    else
    {
        printf("User realized a request size of %zu... found spacing N%i, class_index N%i\n", size, spacing, class);
        printf("Matching size class is : %i\n", size_req);
        run = (run_t*)arena->_tcache_[spacing][class].address;
        printf("Selected run adress is : %p\n", run);
    }
    
    int slot = find_free_slot(run, size_req);
    if (slot == -1)
    {
        mark_size_class(spacing, class, &arena->binmap);
        ptr = req_slot(size);
        return (void*)ptr;
        
    }
    printf("Free slot index is : %i\n", slot);
    set_in_bmp(run, slot, true);
    int offset = slot * size_req;
    int run_size = sizeof(run_t);
    ptr = (void*)run + run_size + offset;
    printf("Total offset is : %i\n", run_size + offset);
    return (void*)ptr;
}