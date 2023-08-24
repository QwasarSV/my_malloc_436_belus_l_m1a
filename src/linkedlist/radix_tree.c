#include <main_header.h>

radix_t* create_node(void* ptr)
{
    // radix_t *node = allocated_node;
    radix_t *node = fetch_node();
    node->ptr = ptr;
    node->left = node->right = NULL;
    return node;
}

// void insert(radix_t** root, void *ptr)
// {
//     if (!(*root))
//     {
//         *root = create_node(ptr);
//         return;
//     }
//     uintptr_t address = (uintptr_t)ptr;
//     radix_t* curr = *root;
//     int bit_index = sizeof(void*) * 8 - 1;
//     while (bit_index >= 0)
//     {
//         if ((address >> bit_index) & 1)
//         {
//             if (!curr->right)
//             {
//                 curr->right = create_node(ptr);
//                 return;
//             }
//             curr = curr->right;
//         }
//         else
//         {
//             if (!curr->left)
//             {
//                 curr->left = create_node(ptr);
//                 return;
//             }
//             curr = curr->left;
//         }
//         bit_index -= 1;
//     }
// }

void insert(radix_t** root, void *ptr)
{
    if (!(*root))
    {
        *root = create_node(ptr);
        return;
    }
    uintptr_t address = (uintptr_t)ptr;
    radix_t* curr = *root;
    int bit_index = sizeof(void*) * 8 - 1;
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
        if(curr->ptr == NULL)
        {
            curr->ptr = ptr;
        }
      bit_index -= 1;
    }
}


radix_t* next_child(radix_t* child_01, radix_t* child_02)
{
    if (child_01)
    {   
        return child_01;
    } 
    else if (child_02)
    {
        return child_02;
    } 
    else
    {
        return NULL;
    }
}

radix_t* next_bit(radix_t* root, bool true_false)
{
    radix_t* tmp = NULL;
    if (true_false)
    {
        if ((tmp = next_child(root->right, root->left)))
        {
            return tmp;
        }
        else 
        {
            return NULL;
        }
    }
    else
    {
        if ((tmp = next_child(root->left, root->right)))
        {
            return tmp;
        }
        else 
        {
            return NULL;
        }
    }
}

uintptr_t validate_run(uintptr_t run_address, uintptr_t address, uintptr_t highest_last_address)
{
    void* ptr = (void*)run_address;
    run_t* run = (run_t*)ptr;
    int size_run = 0;
    if (run->size_class > 14336)
    {
        size_run = run->size_class + sizeof(run_t);
    }
    else
    {
        size_run = sizeof(run_t) + run->size_class * 8 * BITMAP_SIZE;
    }
    uintptr_t run_end = (uintptr_t)ptr + size_run;
    if (address < run_end)
    {
        return run_address;
    }
    return highest_last_address;
}

// void* find_run_start(radix_t* root, void *ptr)
// {
//     uintptr_t address = (uintptr_t)ptr;
//     uintptr_t highest_last_address = (uintptr_t)NULL;
//     uintptr_t current_address = (uintptr_t)NULL;
//     int bit_index = sizeof(void*) * 8 - 1; 
//     radix_t* tmp = NULL;
//     while (bit_index >= 0)
//     {
//         if (!(tmp = next_bit(root, (address >> bit_index) & 1)))
//         {
//             break;
//         }
//         root = tmp;
//         current_address = (uintptr_t)root->ptr;
//         // if (current_address == NULL)
//         // {
//         //     continue;
//         // }
//         if (current_address == address)
//         {
//             return (void*)current_address;
//         }
//         if (current_address > highest_last_address && current_address < address)
//         {
//             highest_last_address = validate_run(current_address, address, highest_last_address);
//         }
//         bit_index -= 1;
//     }
//     return (void*)highest_last_address;
// }

void release_run_start(radix_t* root, void *ptr)
{
    // uintptr_t address = (uintptr_t)ptr;
    // uintptr_t highest_last_address = (uintptr_t)NULL;
    // uintptr_t current_address = (uintptr_t)NULL;
    // int bit_index = sizeof(void*) * 8 - 1; 
    // radix_t* tmp = NULL;
    // while (bit_index >= 0)
    // {
    //     if (!(tmp = next_bit(root, (address >> bit_index) & 1)))
    //     {
    //         break;
    //     }
    //     root = tmp;
    //     current_address = (uintptr_t)root->ptr;
    //     if (current_address == address)
    //     {
    //         root->ptr = NULL;
    //         return;
    //     }
    //     bit_index -= 1;
    // }
}

void* find_run_start(radix_t* root, void* ptr)
{
    uintptr_t highest_last_address = (uintptr_t)NULL;
    uintptr_t current_address = (uintptr_t)NULL;
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
        // printf("requesting memory for radix_tree\n");
        // void* ptr = req_slot(14336);
        void * ptr = get_mem_chunck(4096);
        int size = 4096 / sizeof(radix_t) - 1;
        init_memory_segment(ptr, size);
        new_node = allocate_node();
    }
    return new_node;
}

