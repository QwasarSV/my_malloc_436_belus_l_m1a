#include <main_header.h>

int my_free(void* ptr)
{
    int slot = 0;
    run_t* run;
    clear_in_bmp(run, slot);
    run->last_known_free_position = slot;
    return EXIT_SUCCESS;
}

int close_run(int spacing_index, int class_index)
{
    // arena->binmap[spacing_index][class_index] = false;
}

void* req_slot(size_t size)
{
    int spacing_index = nearest_spacing_index(size);
    int class_index = get_size_class_index(spacing_index, size);
    printf("User realized a request size of %i... found spacing N%i, class_index N%i\n", size, spacing_index, class_index);
    int size_req = size_class[spacing_index][class_index];
    printf("Matching size class is : %i\n", size_req);
    run_t* curr_run = (run_t*)arena->_tcache_[spacing_index][class_index].address;
    printf("Selected run adress is : %p\n", curr_run);
    int slot_index = find_free_slot(curr_run, size_req);
    if (slot_index == -1)
    {
        //request new run of size n;
    }
    printf("Free slot index is : %i\n", slot_index);
    set_in_bmp(curr_run, slot_index, true);
    int offset = slot_index * size_req;
    int run_size = sizeof(run_t);
    void* ptr = (void*)curr_run + run_size + offset;
    // void* ptr = curr_run + BITMAP_SIZE + (sizeof(int)*2) + size_req * slot_index - 1;
    printf("Offset is : %i\n", run_size + offset);
    return (void*) ptr;
}