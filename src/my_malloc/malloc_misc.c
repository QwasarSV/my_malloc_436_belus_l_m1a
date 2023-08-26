#include <main_header.h>

handler_t* handler = NULL;

int to_page_size(size_t size)
{
    int page_size = sysconf(_SC_PAGESIZE);
    int new_size = 0;
    new_size = size + (page_size - size % page_size);
    return new_size;
}

int calc_nb_slot(size_t size, int nb_page)
{
    int total_slot = BITMAP_SIZE * 8;
    // int len = (int) ( ((float) total_slot / (nb_page * handler->size_page)) * size );
    int len = (int) ( ((float) total_slot / (nb_page * handler->size_page)) * size + 0.5);
    if (len == 0)
    {
        return 1;
    } 
    return len;
}

int calc_offset(int slot, int nb_page)
{
    int total_slot = BITMAP_SIZE * 8;
    int offset = (nb_page * handler->size_page)/total_slot*slot;
    return offset;
}

void* get_ptr(size_t size)
{
    void* ptr = NULL;
    tee_t* tee = NULL;
    bmp_t* bmp = handler->head;
    if (bmp == NULL)
    {
        return NULL;
    }
    int len = calc_nb_slot(size, bmp->nb_page);
    int slot = 0;
    int offset = 0;
    while (bmp != NULL)
    {
        slot = find_free_slot(bmp, len);
        if (slot != -1)
        {
        set_bits(bmp, slot, len, true);
        offset = calc_offset(slot, bmp->nb_page);
        // printf("Offset: %i | slot: %i | len: %i\n",offset, slot, len);
        tee = (tee_t*)bmp + offset;
        tee->nb_slot = len;
        // printf("nb_slot : %i, len: %i\n", tee->nb_slot, len);
        // return (void*)bmp + offset;
        return (void*)(tee + 1);
        }
        // printf("bmp val%p\n", bmp);
        bmp = bmp->next;
    }
    return NULL;
}

void set_handler(size_t size_page)
{
    handler->size_page = size_page;
    handler->memory = NULL;
    handler->cursor = 0;
    handler->search_tree = NULL;
    handler->head = NULL;  
}

void initialize_handler()
{
    if (handler == NULL)
    {
        size_t size_page = sysconf(_SC_PAGESIZE);
        void* ptr = mmap(0, size_page, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        handler = ptr;
        set_handler(size_page);
        initialize_bit_list((void*)(handler + 1), 1);
        int len = calc_nb_slot(sizeof(handler_t) + sizeof(bmp_t) + sizeof(page_t), 1);
        set_bits(handler->head, 0, len, true);
        insert(&handler->search_tree, NULL);
        // insert(&handler->search_tree, ptr);
        insert(&handler->search_tree, (handler + 1));
    }
}

page_t* set_page(void* ptr, int nb_page)
{
    page_t* page = ptr;
    // set_bitmap(page);
    page->bmp->nb_page = nb_page;
    page->bmp->next = NULL;
    initialize_bit_list(ptr, nb_page);
    // insert_bmp(&handler->head, page->bmp);
    page->byte = (void*)(page + 1);
    insert(&handler->search_tree, page);
    return page;
}
    
void* req_memory(size_t size)
{
    size_t new_size = to_page_size(size);
    void* ptr = NULL;
    int nb_page = new_size / handler->size_page;
    // ptr = mmap(0, new_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ptr = my_mmap(new_size);
    if (ptr == MAP_FAILED)
    {
        // mmap sets errno appropriately
        return NULL;
    }
    set_page(ptr, nb_page);
    return (void*)ptr;
}

void release_mem(bmp_t* bmp)
{
    void* ptr = (void*)bmp->next;
    if (bmp->next != NULL && is_bitmap_full(bmp->next))
    {
        bmp->next = bmp->next->next;
        size_t size_dealloc = bmp->nb_page * handler->size_page;
        munmap(ptr, size_dealloc);
    }
}