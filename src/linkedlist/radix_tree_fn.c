#include <main_header.h>

radix_t* create_node(void* ptr)
{
    // radix_t *node = allocated_node;
    // printf("creating node\n");
    radix_t *node = fetch_node();
    node->ptr = ptr;
    node->left = node->right = NULL;
    return node;
}


 void insert(radix_t** head, void *ptr)
{
    radix_t* node_to_insert = create_node(ptr);
    node_to_insert->right = *head;
    *head = node_to_insert;
}


// void insert(radix_t** root, void *ptr)
// {
//     if (!(*root))
//     {
//         *root = create_node(ptr);
//         return;
//     }
//     uintptr_t   address     = (uintptr_t)ptr;
//     radix_t*    curr        = *root;
//     int         bit_index   = sizeof(void*) * 8 - 1;
//     while (bit_index >= 0)
//     {
//         if ((address >> bit_index) & 1)
//         {
//             if (!curr->right)
//             {
//                 curr->right = create_node(ptr);
//             }
//             curr = curr->right;
//         } 
//         else
//         {
//             if (!curr->left)
//             {
//                 curr->left = create_node(ptr);
//             }
//             curr = curr->left;
//         }
//         curr->ptr = ptr;
//       bit_index -= 1;
//     }
// }

// void* find_page_start(radix_t* root, void* ptr)
// {
//     radix_t* tmp = root;
//     uintptr_t address = (uintptr_t)ptr;
//     uintptr_t highest = 0;
//     uintptr_t valid = 0;
//     int index = 0;
//     while (tmp != NULL)
//     {
//         index += 1;
//         if (highest < (uintptr_t)tmp->ptr)
//         {
//             highest = (uintptr_t)tmp->ptr;
//             printf("highest %p\n", highest);
//         }
//         if (address > highest)
//         {
//             valid = highest;
//         }
//         tmp = tmp->right;
//     }
//     printf("nb of iteration %i", index);
//     printf("returned address %p\n", valid);
//     return (void*)valid;
// }

void* find_page_start(radix_t* root, void* ptr)
{
    radix_t*   tmp       = root;
    page_t*    page      = NULL;
    int        len_page  = 0;
    uintptr_t  start     = 0;
    uintptr_t  end       = 0;
    uintptr_t  value     = (uintptr_t)ptr;
    while (tmp != NULL)
    {
        page = (page_t*)tmp->ptr;
        len_page = page->bitnode->nb_page * handler->size_page;
        // printf("lenpage %i\n", len_page);
        start = (uintptr_t)tmp->ptr;
        end = (uintptr_t)tmp->ptr + len_page;
        // printf("start value end %i/%i/%i\n", start, value, end);
        if (start < value && value < end)
        {
            // printf("returned address %p\n", tmp->ptr);
            return (void*)tmp->ptr;
        }
        tmp = tmp->right;
        
    }
    
    return NULL;
}


// void* find_page_start(radix_t* root, void* ptr)
// {
//     uintptr_t address = (uintptr_t)ptr;
//     radix_t* curr = root;
//     int bit_index = sizeof(void*) * 8 - 1;
//     while (bit_index >= 0)
//     {
//         if ((address >> bit_index) & 1)
//         {
//             if (!curr->right)
//             {
//                 return curr->ptr;
//             }
//             curr = curr->right;
//         }
//         else
//         {
//             if (!curr->left)
//             {
//                 return curr->ptr;
//             }
//             curr = curr->left;
//         }
//         bit_index -= 1;
//     }
//     return curr->ptr;
// }

radix_t* fetch_node()
{
    radix_t* new_node = NULL;
    new_node = allocate_node();
    if (new_node == NULL)
    {
        // printf("size page is : %i\n",handler->size_page);    
        void * ptr = my_mmap(handler->size_page);
        int size = handler->size_page / sizeof(radix_t) - 1;
        init_memory_segment(ptr, size);
        new_node = allocate_node();
    }
    return new_node;
}