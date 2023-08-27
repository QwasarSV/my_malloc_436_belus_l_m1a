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
    printf("retreiving page from ptr : %p\n", ptr);
    page_t* page = find_page_start(handler->search_tree, (void*)ptr);
    tee_t* tee = (tee_t*)ptr - 1;
    // printf("NB slot is : %i\n", tee->nb_slot);
    printf("found page on tree : %p\n", page);
  
    uintptr_t offset = (uintptr_t)(tee) - (uintptr_t)page->bitnode;
    printf("offset value : %i\n", offset);
    printf("nb_page : %i\n", page->bitnode->nb_page);
    // int start = calc_nb_slot(offset, page->bitnode->nb_page);
    // printf("free :Offset: %i | slot: %i | len: %i\n", offset, start, tee->nb_slot);
    // printf("pos is %i\n", start);
    // set_bits(page->bitnode->bmp, start, tee->nb_slot, false);
    // release_mem(tmp);
  return 0;
}