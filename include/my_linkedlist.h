#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>

#ifndef NODE_S
#define NODE_S
struct node 
{
    bool         used;
    struct node* head;
    struct node* next;
};
typedef struct node chunk_t;
#endif

chunk_t*    create_node(bool used);
void        insert_at_head(chunk_t** head, chunk_t* chunk_to_insert);
void        print_llist(chunk_t* head);
void        free_llist(chunk_t* head);

#endif
