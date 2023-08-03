#include <main_header.h>

mseg_t* register_node_data(mseg_t* new_node, size_t size, bool isfree, void* ptr)
{
    new_node->size_chunk = size;
    new_node->isfree = isfree;
    new_node->ptr_cmp = ptr;
    new_node->next = NULL;
    return new_node;
}

void insert_at_head(mseg_t** head, mseg_t* mseg_to_insert)
{
    mseg_to_insert->next = *head;
    *head = mseg_to_insert;
}

void print_llist(mseg_t* head)
{
    mseg_t* iterator = head; 
    printf("printing the llist:\n");
    while (iterator != NULL)
    {
        printf("%p-",iterator->ptr_cmp);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

// void free_llist(mseg_t* head)
// {
//     mseg_t* tmp = NULL;
//     while ( head != NULL)
//     {
//         tmp = head;
//         head = head->next;
//         free(tmp);
//     }
// }