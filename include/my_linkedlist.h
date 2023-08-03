#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>

#ifndef NODE_S
#define NODE_S
struct node
{
    bool         used;
    void*        chunk_address; 
    struct node* head;
    struct node* next;
};
typedef struct node chunk_t;
#endif

extern chunk_t* head;
extern char* memory;

mseg_t*     register_node_data(mseg_t* new_node, size_t size, bool isfree, void* ptr);
void        insert_at_head(mseg_t** head, mseg_t* mseg_to_insert);
void        print_llist(mseg_t* head);
void        free_llist(chunk_t* head);

#endif