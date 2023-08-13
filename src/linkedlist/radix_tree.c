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
                return;
            }
            curr = curr->right;
        }
        else
        {
            if (!curr->left)
            {
                curr->left = create_node(ptr);
                return;
            }
            curr = curr->left;
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


void* find_run_start(radix_t* root, void *ptr)
{
    uintptr_t address = (uintptr_t)ptr;
    uintptr_t highest_last_address = (uintptr_t)NULL;
    uintptr_t current_address = (uintptr_t)NULL;
    int bit_index = sizeof(void*) * 8 - 1; 
    radix_t* tmp = NULL;
    while (bit_index >= 0)
    {
        if (!(tmp = next_bit(root, (address >> bit_index) & 1)))
        {
            break;
        }
        root = tmp;
        current_address = (uintptr_t)root->ptr;
        if (current_address == address)
        {
            return (void*)current_address;
        }
        if (current_address > highest_last_address && current_address < address)
        {
            highest_last_address = current_address;
        }
        bit_index += 1;
    }
    return (void*)highest_last_address;
}

radix_t* fetch_node()
{
    radix_t* new_node = NULL;
    if (!(new_node = allocate_node()))
    {
        void* ptr = req_slot(14336);
        init_memory_segment(ptr, 14336);
        new_node = allocate_node();
    }
    return new_node;
}

// void free_radix_tree(radix_t* root) {
//    if (!root) return;
//     freeRadixTree(root->left);
//     freeRadixTree(root->right);
//     // free(root);
// }