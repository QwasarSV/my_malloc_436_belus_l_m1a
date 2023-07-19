#include <main_header.h>

// #include <string.h>
// void* my_malloc(int size) {
//   return mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
// }

char *memory = NULL;
chunk_t* head;

void init_mem_tracker()
{
    chunk_t* tmp = NULL;
    int nb_chunk = 0;
    while (nb_chunk < _CALL_SIZE_/_CHUNK_SIZE_)
    {
        tmp = create_node(false); 
        insert_at_head(&head, tmp);
        nb_chunk += 1;
    }
}

void mark_chunk(int start, int nb_chunk)
{
    int index = 0;
    int count = 0;
    chunk_t* iterator = head;
    while (iterator != NULL && count < nb_chunk)
    {
        if (index >= start)
        {
            iterator->used = true;
            count += 1;
        }
        index += 1;
        iterator = iterator->next;
    }
    printf("%i chunk were marked as used\n", index);
}

// #define _NOT_FOUND_ = -1

int is_request_avalaible(int pos, int chunk_req, chunk_t* iterator)
{
    chunk_t* tmp = iterator;
    int count = 0;
    while (tmp != NULL & count < chunk_req)
    {
        if (tmp->used == true)
        {
            iterator = tmp;
            return count;
        }
        count += 1;
        tmp = tmp->next;
    }
    printf("Preparing to mark %i chunk...\n", chunk_req);
    mark_chunk(pos, chunk_req);
    return EOF;
}


int find_start(int chunk_req)
{
    int index = 0;
    int start = 0;
    int count = 0;
    chunk_t* iterator = head;
    while (iterator != NULL)
    {
        if ((count = is_request_avalaible(index, chunk_req, iterator)) == -1)
        {
            return index;
        }
        else
        {
            index += count;
        }
        index += 1;
        iterator = iterator->next;
    }
    return EOF;
}

int set_call_size(size_t size)
{
    if (size > _CALL_SIZE_)
    {
        return size;
    }
    return _CALL_SIZE_
}

void* my_malloc(size_t size)
{
    int size = set_call_size(size);

    if (memory == NULL || size > _CALL_SIZE_)
    {
        memory = my_mmap(size);
        init_mem_tracker();
    }
    int chunk_req = (size + _CHUNK_SIZE_ - 1) / _CHUNK_SIZE_;
    printf("Requesting %i chunk...\n", chunk_req);
    int start_chunk = 0;
    if ((start_chunk = find_start(chunk_req)) == -1) 
    {
        //realloc
    }
    // mark_chunk(start_chunk, chunk_needed);
    void *ptr = memory + start_chunk * _CHUNK_SIZE_;

    return ptr;
}

// void* my_malloc()
// {
//     return my_mmap();
// }

int main(int ac, char **av)
{
    char *src = "hello";
    char *dest_01 = my_malloc(my_strlen(src) + 150);
	// int dest = my_malloc();
    print_llist(head);
    my_strcpy(dest_01, src);
    printf("%s\n", dest_01);
    char *dest_02 = my_malloc(my_strlen(src) + 2);
    print_llist(head);
    my_strcpy(dest_02, src);
    printf("%s\n", dest_02);
    free_llist(head);
    return 0;
}