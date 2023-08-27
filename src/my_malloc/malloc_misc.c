#include <main_header.h>

handler_t* handler = NULL;

int to_page_size(size_t size)
{
    int page_size = sysconf(_SC_PAGESIZE);
    int total_size = size +sizeof(page_t);
    int new_size = 0;
    new_size = total_size + (page_size - total_size % page_size);
    printf("size_req to mmap : %i\n", new_size);
    return new_size;
}

int calc_nb_slot(size_t size, int nb_page)
{
    int total_slot = BITMAP_SIZE * 8;
    // int len = (int) ( ((float) total_slot / (nb_page * handler->size_page)) * size );
    int len = (int) (((float) total_slot / (nb_page * handler->size_page)) * size + 0.5);
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
    bitlist_t* tmp = handler->head;
    if (tmp == NULL)
    {
        return NULL;
    }
    int len = calc_nb_slot(size, tmp->nb_page);
    int slot = 0;
    int offset = 0;
    while (tmp != NULL)
    {
        slot = find_free_slot(tmp->bmp, len);
        if (slot != -1)
        {
            set_bits(tmp->bmp, slot, len, true);
            offset = calc_offset(slot, tmp->nb_page);
            printf("malloc :Offset: %i | slot: %i | len: %i\n",offset, slot, len);
            tee = (tee_t*)tmp + offset;
            tee->nb_slot = len;
            tee->magic_number = MAGIC_NUMBER;
            // printf("nb_slot : %i, len: %i\n", tee->nb_slot, len);
            // return (void*)bmp + offset;
            return (void*)(tee + 1);
        }
        // printf("bmp val%p\n", bmp);
        tmp = tmp->next;
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
        ptr = set_page((void*)(handler + 1), 1);
        // initialize_bit_list((void*)(handler + 1), 1);
        int len = calc_nb_slot(sizeof(handler_t) + sizeof(bitlist_t) + sizeof(page_t), 1);
        set_bits(handler->head->bmp, 0, len, true);
        insert(&handler->search_tree, NULL);
        // insert(&handler->search_tree, ptr);
        insert(&handler->search_tree, (void*)ptr);
    }
}

page_t* set_page(void* ptr, int nb_page)
{
    page_t* page = (page_t*) ptr;
    bitlist_t* bitlist = (bitlist_t*) (((char*)ptr) + sizeof(page_t));
    char* byte = ((char*)bitlist) + sizeof(bitlist_t);
    page->bitnode = bitlist;
    // page->bitnode->nb_page = nb_page;
    // page->bitnode->next = NULL;
    initialize_bit_list((void*)page->bitnode, nb_page);
    page->byte = byte;
    printf("insert page on tree : %p\n", page);
    insert(&(handler->search_tree), page);
    return page;
    // page_t* page = ptr;
    // page->bitnode = ptr + sizeof(page_t);
    // page->bitnode->nb_page = nb_page;
    // page->bitnode->next = NULL;
    // initialize_bit_list(ptr, nb_page);
    // page->byte = (void*)(sizeof(page_t)+sizeof(bitlist_t));
    // insert(&handler->search_tree, page);
    // return page;
    // char* char_ptr = (char*)ptr;
    // page_t* page = (page_t*)char_ptr;
    // char_ptr += sizeof(page_t);
    // page->bitnode = (bitlist_t*)char_ptr;
    // char_ptr += sizeof(bitlist_t);
    // page->bitnode->nb_page = nb_page;
    // page->bitnode->next = NULL;
    // initialize_bit_list(page->bitnode, nb_page);
    // page->byte = char_ptr;
    // insert(&handler->search_tree, page);
    // return page;
}
 
void* req_memory(size_t size)
{
    size_t new_size = to_page_size(size);
    void* ptr = NULL;
    int nb_page = new_size / handler->size_page ;
    // ptr = mmap(0, new_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    ptr = my_mmap(new_size);
    if (ptr == MAP_FAILED)
    {
        // mmap sets errno appropriately
        return NULL;
    }
    ptr = set_page(ptr, nb_page);
    return (void*)ptr;
}

void release_mem(bitlist_t* node)
{
    void* ptr = (void*)node->next;
    if (node->next != NULL && is_bitmap_full(node->next))
    {
        node->next = node->next->next;
        size_t size_dealloc = node->nb_page * handler->size_page;
        munmap(ptr, size_dealloc);
    }
}