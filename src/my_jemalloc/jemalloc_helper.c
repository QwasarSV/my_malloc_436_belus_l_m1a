#include <main_header.h>


bool is_within_class_range(size_t size)
{
    if (size > 14336)
    {
        return false;
    }
    return true;
}

void release_slot(run_t* run, void* ptr)
{
    void* run_start = (void*)run + sizeof(run_t);
    // printf("Run is size_class: %i \n", run->size_class);
    int slot = ((uintptr_t)ptr - (uintptr_t)run_start)/run->size_class;
    printf("Freeing slot N: %i \n", slot);
    clear_in_bmp(run, slot);
    run->last_known_free_position = slot;
}


int to_page_size(size_t size)
{
    int page_size = sysconf(_SC_PAGESIZE);
    int new_size = 0;
    new_size = size + (page_size - size % page_size);
    return new_size;
}

int to_size_class(size_t size)
{
    int new_size = 0;
    int spacing = nearest_spacing_index(size);
    int class = get_size_class_index(spacing, size);
    
    if (class != -1)
    {
        new_size = size_class[spacing][class];
        return new_size;
    }
    return -1;
}

// not good to recode//
arena_t* find_binmap(void* ptr)
{
    uintptr_t address = (uintptr_t)ptr;
    uintptr_t current_address = 0;
    uintptr_t highest_last_address = 0;
    arena_t*  arena = NULL; 
    node_t*   iterator = handler->arenas_list;

    while (iterator != NULL)
    {
        current_address = (uintptr_t)iterator->arena->_tcache_[0][0].address;
        if (current_address == ptr)
        {
            return iterator->arena;;
        }
        if (current_address > highest_last_address
        &&  current_address < address)
        {
            highest_last_address = current_address;
            arena = iterator->arena;
        }
        iterator = iterator->next;
    }
    return arena;
}

int find_next_size_class(arena_t* arena, int spacing, int class)
{
    int run_req = size_class[spacing][class];
    //patch : /!\ WASTE OF BYTES /!\ need to mark as used slot on the end of run, and call a higher size_class.
    run_req *=  BITMAP_SIZE * 8 + sizeof(run_t);
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
    int page_size = sysconf(_SC_PAGESIZE);
    if (handler->memory == NULL)
    {
        handler->memory = (void*)my_mmap(mem_call_size);
        handler->mem_pos = 0;
    }
    else if (handler->memory != NULL && (left_over <= size_req || left_over < page_size))
    {
        printf("REQUESTING MEMORY CHUNK : %i\n", mem_call_size);
        munmap(handler->memory, left_over);
        handler->memory = (void*)my_mmap(mem_call_size);
        handler->mem_pos = 0;
    }
}

void* get_mem_chunck(size_t size_req)
{
    void* ptr = NULL; 
    pool_mem_req(size_req);
    
    // printf("Finding adress at :%p\n", find_run_start(handler->root, handler->memory));
    ptr = handler->memory;
    int offset = sizeof(run_t) + size_req;
    handler->memory = (void*)handler->memory + offset;
    handler->mem_pos += offset;
    return (void*)ptr;
}

run_t* set_run(void* ptr, size_t size)
{
    run_t* run = ptr;
    set_bitmap(run);
    run->size_class = size;
    run->is_locked = false;
    run->last_known_free_position = 0;
    run->next = NULL;
    run->byte = (void*)(run + 1);
    // insert_run_on_radix_tree((void*)run);
    return run;
}