#include <main_header.h>

// node_t* create_arena_node(arena_t* arena)
// {
//     // node_t* new_node = req_slot(sizeof(node_t));
//     new_node->arena = arena;
//     new_node->next = NULL;
//     return new_node;
// }

void insert_arena_at_head(node_t** head,node_t* node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}

