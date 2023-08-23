#include <main_header.h>

void* my_malloc(size_t size)
{    
    void* ptr = NULL;
    
    if (handler == NULL)
    {
        create_mem_handler();
    }

    ptr = req_slot_on_global(size);
    return (void*)ptr;
}

int my_free(void* ptr)
{
    run_t* run = find_run_start(handler->root, (void*)ptr);
    free_global_slot(run, ptr);
    return EXIT_SUCCESS;
}

// void* req_slot(size_t size);

// // to rm
// int my_free(void* ptr)
// {
//     run_t* run = find_run_start(handler->root, (void*)ptr);
//     printf("The run start for address %p is %p\n", ptr, run);
//     printf("run size_class is : %i\n", run->size_class);
//     if (run->size_class > 14336)
//     {
//         release_run_start(handler->root, (void*)run);
//         munmap(run, run->size_class);
//         return EXIT_SUCCESS;
//     }
//     // printf("The run start for address %p is %p\n", ptr, run);
//     void* run_start = (void*)run + sizeof(run_t);
//     // printf("Run is size_class: %i \n", run->size_class);
//     int slot = ((uintptr_t)ptr - (uintptr_t)run_start)/run->size_class;
//     // printf("Freeing slot N: %i \n", slot);
//     clear_in_bmp(run, slot);
//     run->last_known_free_position = slot;
//     arena_t* arena = find_binmap((void*)run);
//     // printf("Run TID is: %lu \n", arena->tid);
//     int spacing = nearest_spacing_index(run->size_class);
//     // printf("Run is spacing: %i \n", spacing);
//     int class_index = get_size_class_index(spacing, run->size_class);
//     free_size_class(spacing, class_index, &arena->binmap);
//     return EXIT_SUCCESS;
// }

// // to rm
// run_t* create_new_run(arena_t* arena, size_t spacing, size_t class)
// {
//     int size_req = find_next_size_class(arena, spacing, class);
//     void* ptr = NULL;
//     run_t* run = NULL;
//     if (size_req == -1)
//     {
//         size_req = size_class[spacing][class] * BITMAP_SIZE * 8;
//         ptr = get_mem_chunck(size_req);
//         // insert_run_on_radix_tree(ptr);
//     }
//     else 
//     {
//         ptr = req_slot(size_req);
//         insert_run_on_radix_tree(ptr);
//         size_req = size_class[spacing][class];
//     }
//     run = set_run(ptr, size_class[spacing][class]);
//     // set_bitmap(run);
//     insert_run_at_head(&handler->pool, run);
//     free_size_class(spacing, class, &handler->binmap);
//     int result = is_size_class_free(spacing, class, &handler->binmap);
//     return run;
// }
// // to rm
// run_t* get_or_create_run(arena_t* arena, int spacing, int class)
// {
//     run_t* run = NULL;
//     int size_req = size_class[spacing][class];
//     if (is_size_class_free(spacing, class, &handler->binmap))
//     {
//         run = search_pool(size_req);
//         // printf("found run :%p for class : %i, %i, %i\n", run, spacing, class, size_req);
//         // quick patch to remove. mark bitmap before.
//         // if (run == NULL)
//         // {
//         //     run = create_new_run(arena, spacing, class);    
//         // }
//         if (is_bitmap_full(run))
//         {
//             mark_size_class(spacing, class, &handler->binmap);
//             run = get_or_create_run(arena, spacing, class);
//         }
//     }
//     else
//     {
//         run = create_new_run(arena, spacing, class);
//         free_size_class(spacing, class, &handler->binmap);
//     }
//     return run;
// }

// // to rm
// run_t* find_run(arena_t* arena, int spacing, int class)
// {
//     run_t* run = NULL;
//     if (!is_size_class_free(spacing, class, &arena->binmap))
//     {
//         run = get_or_create_run(arena, spacing, class);
//     }
//     else
//     {
//         run = (run_t*)arena->_tcache_[spacing][class].address;
//     }
//     return run;
// }

// // to rm
// void* req_slot(size_t size)
// {
//     run_t* run = NULL;
//     void* ptr = NULL;
//     arena_t* arena = find_arena();
//     int spacing = nearest_spacing_index(size);
//     int class = get_size_class_index(spacing, size);
//     if (class == -1)
//     {
//         //patch: should follow a run/bitmap logic until large class and then resolve to mmap;
//         // here it stop at medium size and then mmap;
//         long page_size = sysconf(_SC_PAGESIZE);
//         int new_size = size + sizeof(run_t);
//         int custom_size = new_size + (page_size - new_size % page_size);
//         ptr = get_mem_chunck(custom_size);
//         // ptr = my_mmap(custom_size);
//         run = (run_t*)ptr;
//         run->size_class = custom_size;
//         ptr = ptr + sizeof(run_t);

//         // ptr = get_mem_chunck((size * BITMAP_SIZE * 8) + sizeof(run_t));
//         // run = set_run(ptr, size);
//         // insert_run_at_head(&handler->pool, run);
//         // free_size_class(spacing, class, &handler->binmap);
//         // insert_run_on_radix_tree(run);
//         return (void*)ptr;
//     }
//     else
//     {
//         // printf("User realized a request size of %zu... found spacing N%i, class_index N%i\n", size, spacing, class);
//         run = find_run(arena, spacing, class);
//     }
//     int size_req = 0;
//     size_req = size_class[spacing][class];
//     // printf("Matching size class is : %i\n", size_req);
//     // printf("Selected run adress is : %p\n", run);

//     int slot = find_free_slot(run);
//     if (slot == -1)
//     {
//         mark_size_class(spacing, class, &arena->binmap);
//         ptr = req_slot(size);
//         return (void*)ptr;
//     }
//     // printf("Free slot index is : %i\n", slot);
//     set_in_bmp(run, slot, true);
//     int offset = slot * size_req;
//     int run_size = sizeof(run_t);
//     ptr = (void*)run + run_size + offset;
//     // printf("Total offset is : %i\n", run_size + offset);
//     return (void*)ptr;
// }

// // to rm
// void* my_malloc(size_t size)
// {
//     void* ptr = NULL;
//     if (handler == NULL)
//     {
//         create_mem_handler();
//         ptr = req_slot(size);
//     }
//     else
//     {
//         ptr = req_slot(size);
//     }
//     return (void*)ptr;
// }

