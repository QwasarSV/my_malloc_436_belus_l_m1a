#include <main_header.h>

g_pool_t* handler = NULL;

size_t handler_size_req()
{
    size_t size_arena      = arena_size_req();
    size_t size_handler    = sizeof(g_pool_t);
    size_t size_req        = size_arena + size_handler + 1;
    return size_req;
}

void* req_mem_for_handler()
{
    size_t size_req = handler_size_req();
    char* memory    = my_mmap(size_req);
    return (void*)memory;
}

void create_mem_handler(void)
{   
    size_t size_handler    = sizeof(g_pool_t); 
    void* memory = req_mem_for_handler();
    void* node_start = memory + size_handler + 1;
    handler = (g_pool_t*)memory;
    handler->arenas_list = node_start;
    void* arena_start = (void*)memory + size_handler + sizeof(node_t) + 1;
    create_arena(arena_start);
    handler->arenas_list->next = NULL;
}

arena_t* find_arena()
{
    node_t* iterator = handler->arenas_list;
    return handler->arenas_list->arena;
    while (iterator != NULL)
    {
        if (iterator->arena->tid == (unsigned long)pthread_self())
        {
            return iterator->arena;
        }
        iterator = iterator->next;
    }
    return NULL; 
}