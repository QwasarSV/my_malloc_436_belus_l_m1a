#include <main_header.h>

handler_t* handler = NULL;

int to_page_size(size_t size)
{
    int page_size = sysconf(_SC_PAGESIZE);
    int total_size = size +sizeof(page_t);
    int new_size = 0;
    new_size = total_size + (page_size - total_size % page_size);
    // printf("size_req to mmap : %i\n", new_size);
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
    return len  +1;
}

int calc_offset(int slot, int nb_page)
{
    int total_slot = BITMAP_SIZE * 8;
    int offset = ((nb_page * handler->size_page) / total_slot) * slot;
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
        if (slot + len >= BITMAP_SIZE * 8)
        {
            return NULL;
        }
        if (slot != -1)
        {
            set_bits(tmp->bmp, slot, len, true);
            offset = calc_offset(slot, tmp->nb_page);
            // printf("malloc :Offset: %i | slot: %i | len: %i\n",offset, slot, len);
            tee = (tee_t*)((char*)tmp + offset);
            tee->nb_slot = len;
            tee->magic_number = MAGIC_NUMBER;
            // printf("nb_slot : %i, len: %i\n", tee->nb_slot, len);
            // return (void*)bmp + offset;
            handler->memory = (void*)(tee + 1);
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
        int len = calc_nb_slot(sizeof(handler_t) + sizeof(bitlist_t) + sizeof(page_t), 1);
        set_bits(handler->head->bmp, 0, len, true);
        // insert(&handler->search_tree, NULL);
        // insert(&handler->search_tree, (void*)ptr);
    }
}

page_t* set_page(void* ptr, int nb_page)
{
    page_t* page = (page_t*) ptr;
    bitlist_t* bitlist = (bitlist_t*) (((char*)ptr) + sizeof(page_t));
    char* byte = ((char*)bitlist) + sizeof(bitlist_t);
    page->bitnode = bitlist;
    initialize_bit_list((void*)page->bitnode, nb_page);
    page->byte = byte;
    // printf("insert page on tree : %i\n", (uintptr_t)page);
    insert(&handler->search_tree, page);
    return page;
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

bool is_page_valid(page_t* page, void* ptr)
{
    if ((uintptr_t)page > (uintptr_t)ptr)
    {
        return false;
    }
    uintptr_t offset = (uintptr_t)ptr - (uintptr_t)page->bitnode;
    uintptr_t size_page = page->bitnode->nb_page * handler->size_page;
    if (offset > size_page || offset < 0)
    {
        return false;
    }
    return true;
}

// In need of an algo or tree to handle that.
bitlist_t* retrieve_bitlist(void* ptr)
{
    bitlist_t* tmp       = handler->head;
    uintptr_t  len_page  = 0;
    uintptr_t  start     = 0;
    uintptr_t  end       = 0;
    uintptr_t  value     = (uintptr_t)ptr;
    while (tmp != NULL)
    {
        len_page = tmp->nb_page * handler->size_page;
        start = (uintptr_t)tmp;
        end = start + len_page;
        if (value > start && value < end)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}