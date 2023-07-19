#include <main_header.h>

chunk_t* create_node(bool used)
{
    chunk_t* new_node = malloc(sizeof(chunk_t));
    new_node->used = used;
    new_node->next = NULL;
    new_node->head = NULL;
    return new_node;
}

void insert_at_head(chunk_t** head, chunk_t* chunk_to_insert)
{
    chunk_to_insert->next = *head;
    *head = chunk_to_insert;
}

void print_llist(chunk_t* head)
{
    chunk_t* iterator = head; 
    printf("printing the llist:\n");
    while (iterator != NULL)
    {
        printf("%i-",iterator->used);
        iterator = iterator->next;
    }
    printf("NULL\n");
}

void free_llist(chunk_t* head)
{
    chunk_t* tmp = NULL;
    while ( head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}