#include <main_header.h>
radix_t* create_node(void* ptr)
{
    // radix_t *node = allocated_node;
    radix_t *node = malloc(sizeof(radix_t));
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