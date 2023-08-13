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

int create_new_run(arena_t* arena, int spacing, int class)
{
    int size_req = find_next_size_class(arena, spacing, class);
    void* ptr = req_slot(size_req);
    insert_run_on_radix_tree(ptr);
    run_t* run = ptr;
    run->byte = ptr + BITMAP_SIZE + 1;
}


void* req_slot(size_t size)
{
    arena_t* arena = find_arena();
    int spacing_index = nearest_spacing_index(size);
    int class_index = get_size_class_index(spacing_index, size);
    if (!is_size_class_free(spacing_index, class_index, &arena->binmap))
    {   
        create_new_run(arena, spacing_index, class_index);
    }
    printf("User realized a request size of %zu... found spacing N%i, class_index N%i\n", size, spacing_index, class_index);
    int size_req = size_class[spacing_index][class_index];
    printf("Matching size class is : %i\n", size_req);
    run_t* curr_run = (run_t*)arena->_tcache_[spacing_index][class_index].address;
    printf("Selected run adress is : %p\n", curr_run);
    int slot_index = find_free_slot(curr_run, size_req);
    if (is_bitmap_full(curr_run))
    {
        mark_size_class(spacing_index, class_index, &arena->binmap);
    }
    printf("Free slot index is : %i\n", slot_index);
    set_in_bmp(curr_run, slot_index, true);
    int offset = slot_index * size_req;
    int run_size = sizeof(run_t);
    void* ptr = (void*)curr_run + run_size + offset;
    printf("Total offset is : %i\n", run_size + offset);
    return (void*) ptr;
}