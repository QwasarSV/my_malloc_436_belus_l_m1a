#include <main_header.h>

void* my_malloc(size_t size)
{
    if (size > PTRDIFF_MAX)
    {
        errno = EINVAL;
        return NULL;
    }
    void* ptr = NULL;
    initialize_handler();
    size_t size_req = size + sizeof(tee_t);
    ptr = get_ptr(size_req);
    
    if (ptr == NULL)
    {
        req_memory(size_req);
        ptr = get_ptr(size_req);
    }
    return ptr;
}

int my_free(void* ptr)
{
    bmp_t* bmp = find_page_start(handler->search_tree, (void*)ptr);
    tee_t* tee = (tee_t*)ptr - 1;
    // printf("NB slot is : %i\n", tee->nb_slot);
    // printf("found page on tree : %p\n", bmp);
  
    uintptr_t offset = (uintptr_t)ptr - (uintptr_t)bmp;
    // printf("offset value : %i\n", offset);
    // printf("nb_page : %i\n", bmp->nb_page);
    int start = calc_nb_slot(offset, bmp->nb_page);
    // printf("pos is %i\n", start);
    set_bits(bmp, start, tee->nb_slot, false);
    release_mem(bmp);
  return 0;
}