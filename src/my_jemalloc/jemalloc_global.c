#include <main_header.h>

int free_global_slot(run_t* run, void* ptr)
{
    if (run == NULL)
    {
        // set errno
        printf("FAILLING AT RUN RETRIEVAL\n");
        return EXIT_FAILURE;
    }
    printf("Run is address: %p \n", (void*)run);
    printf("Run is size_class: %i \n", run->size_class);
    if (is_within_class_range(run->size_class))
    {
        release_slot(run, ptr);
        // need to rearrange linkelist befor release. 
        // for future update once data structure matured enough;
        release_global_run(run);
    }
    else
    {
        release_run_start(handler->root, (void*)run);
        munmap(run, run->size_class);
    }
    return EXIT_SUCCESS;
}

void* create_custom_sized_run(size_t size)
{
    void* ptr = NULL;
    run_t* run = NULL;
    int new_size = to_page_size(size + sizeof(run_t));
    ptr = request_memory(new_size);
    run = set_run(ptr, new_size);
    ptr = (void*)ptr + sizeof(run_t);
    insert_run_on_radix_tree(run);
    return (void*)ptr;
}

void* get_slot(run_t* run, size_t size_req)
{
    void* ptr = NULL;
    int slot = find_free_slot(run);
    printf("Free slot index is : %i\n", slot);
    set_in_bmp(run, slot, true);
    int offset = (slot) * size_req;
    int run_size = sizeof(run_t);
    ptr = (void*)run + run_size + offset;
    return ptr;
}

void* req_slot_on_global(size_t size)
{
    run_t* run = NULL;
    void* ptr = NULL;
    int size_req = to_size_class(size);
    if (is_within_class_range(size))
    {
        run = request_run_from_pool(size);
    }
    else
    {
        ptr = create_custom_sized_run(size);
        return (void*)ptr;
    }
    ptr = get_slot(run, size_req);
    return (void*)ptr;
}


void* request_memory(size_t size)
{
    void* ptr = NULL;
    // pool_mem_req(size);
    ptr = get_mem_chunck(size);
    // ptr = (void*)set_run(ptr, size);
    // ptr = ptr + sizeof(run_t) + 1;
    return ptr;
}

run_t* create_from_memory(size_t size)
{
    void* ptr = NULL;
    run_t* run = NULL;
    int size_req = size * BITMAP_SIZE * 8 + sizeof(run_t);
    int new_size_req = to_page_size(size_req);
    ptr = request_memory(new_size_req);
    run = set_run(ptr, size);
    insert_run_on_radix_tree(run);
    return run;
}

bool is_class_pool_free(size_t size)
{
    int spacing = nearest_spacing_index(size);
    int class = get_size_class_index(spacing, size);
    return is_size_class_free(spacing, class, &handler->binmap);
}


void free_class_pool(size_t size)
{
    int spacing = nearest_spacing_index(size);
    int class = get_size_class_index(spacing, size);
    free_size_class(spacing, class, &handler->binmap);
}


run_t* request_run_from_pool(int size)
{
    int class_req = to_size_class(size);
    run_t* run = NULL;
    if (is_class_pool_free(size))
    {
        run = search_pool(class_req);
        printf("found run at %p\n", (void*)run);
        if (is_bitmap_full(run))
        {
            run = NULL;
        }
    }
    if (run == NULL)
    {
        run = create_from_memory(class_req);
        insert_run_at_head(&handler->pool, run);
        free_class_pool(class_req);
    }
    return run;
}

void release_global_run(run_t* run)
{
    if (is_bitmap_clear(run))
    {
        printf("RELEASING MEM TO SYSTEM\n");
        // release_run_start(handler->root, (void*)run);
        int size_req = run->size_class * BITMAP_SIZE * 8 + sizeof(run_t);
        int new_size_req = to_page_size(size_req);
        printf("RELEASING MEM TO SYSTEM : %i\n", new_size_req);
        // munmap(run, new_size_req);
    }
}