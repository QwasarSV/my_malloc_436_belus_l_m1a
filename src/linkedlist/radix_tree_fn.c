#include <main_header.h>

radix_t* create_node(void* ptr)
{
    // radix_t *node = allocated_node;
    radix_t *node = fetch_node();
    node->ptr = ptr;
    node->left = node->right = NULL;
    return node;
}

void insert(radix_t** root, void *ptr)
{
    if (!(*root))
    {
        *root = create_node(ptr);
        return;
    }
    uintptr_t   address     = (uintptr_t)ptr;
    radix_t*    curr        = *root;
    int         bit_index   = sizeof(void*) * 8 - 1;
    while (bit_index >= 0)
    {
        if ((address >> bit_index) & 1)
        {
            if (!curr->right)
            {
                curr->right = create_node(ptr);
            }
            curr = curr->right;
        } 
        else
        {
            if (!curr->left)
            {
                curr->left = create_node(ptr);
            }
            curr = curr->left;
        }
        curr->ptr = ptr;
      bit_index -= 1;
    }
}

void* find_page_start(radix_t* root, void* ptr)
{
    uintptr_t address = (uintptr_t)ptr;
    radix_t* curr = root;
    int bit_index = sizeof(void*) * 8 - 1;
    while (bit_index >= 0)
    {
        if ((address >> bit_index) & 1)
        {
            if (!curr->right)
            {
                return curr->ptr;
            }
            curr = curr->right;
        }
        else
        {
            if (!curr->left)
            {
                return curr->ptr;
            }
            curr = curr->left;
        }
        bit_index -= 1;
    }
    return curr->ptr;
}

radix_t* fetch_node()
{
    radix_t* new_node = NULL;
    
    if (!(new_node = allocate_node()))
    {
        printf("size page is : %i\n",handler->size_page);    
        void * ptr = my_mmap(handler->size_page);
        int size = handler->size_page / sizeof(radix_t) - 1;
        init_memory_segment(ptr, size);
        new_node = allocate_node();
    }
    return new_node;
}