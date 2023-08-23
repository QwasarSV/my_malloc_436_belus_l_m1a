#include <main_header.h>

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