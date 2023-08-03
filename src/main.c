#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick

mseg_t* segment_tmp;
mseg_t* segment_head = NULL;
char*   memory = NULL;
int size_tracker = 0;

int set_call_size(size_t size)
{
    if (size > _CALL_SIZE_)
    {
        return size;
    }
    return _CALL_SIZE_;
}

void* add_node(void* ptr, size_t size, bool isfree)
{
    size_tracker += sizeof(mseg_t);
    printf("adding size of struct %d\n",sizeof(mseg_t));
    segment_tmp = (mseg_t*)ptr;
    void* ptr_at = segment_tmp + 1;
    printf("the size on the chunk is size %i\n", size);
    segment_tmp = register_node_data(segment_tmp, size, true, ptr);
    insert_at_head(&segment_head, segment_tmp);
    return ptr_at;
}

void* find_free_chunk(size_t size)
{
    mseg_t* iterator = segment_head;
    void* ptr = NULL;
    while (iterator != NULL)
    {
        
        if (iterator->isfree == true && iterator->size_chunk > size)
        {
            printf("iterator size chunk : %zu, size %zu\n",iterator->size_chunk, size);
            iterator->isfree = false;
            iterator->size_chunk = size;
            ptr = iterator + 1;
            void* next_ptr = ptr + size + sizeof(mseg_t);
            add_node(next_ptr, size, true);
            return ptr; 
        }
        iterator = iterator->next;
    }
    return ptr;
}

void* new_split(size_t size, char* mem_block)
{
    void* ptr = mem_block + sizeof(mseg_t);
    void* ret = add_node(ptr, size, false);
    void* next_ptr = ptr + size + sizeof(mseg_t);
    int remaining_space = _CALL_SIZE_ - size - sizeof(mseg_t) * 2;
    printf("\nthis is the remaining space%d\n", remaining_space);
    add_node(next_ptr, remaining_space, true);
    return (void*) ret;
}

void* my_malloc(size_t size)
{
    int size_req = 0;
    void* ptr = NULL;
    char* mem_block = NULL;
    if (segment_head == NULL)
    {
        size_req = set_call_size(size);
        mem_block = my_mmap(size_req);
        ptr = new_split(size, mem_block);
    }
    else
    {
        ptr = find_free_chunk(size);
        if (ptr == NULL)
        {
            printf("\n\nadding new memory block\n\n");
            size_req = set_call_size(size);
            mem_block = my_mmap(size_req);
            ptr = new_split(size, mem_block);
        }
    }
    //find empty and split it.
    return (void*)ptr;
}

// void* my_malloc()
// {
//     return my_mmap();
// }

void test_for_loop()
{
    char *src = "hello this is a string probleme or maybe a struct issue !!";
    size_tracker += my_strlen(src) + 1;
    printf("string size is : %i\n", my_strlen(src)+1);
    char *dest_01 = my_malloc(my_strlen(src) + 1);
    printf("total used size is :%i\n", size_tracker);
    // int dest = my_malloc();
    // print_llist(segment_head);
    my_strcpy(dest_01, src);
    printf("%s\n", dest_01);
    // print_llist(segment_head);
}


int main(int ac, char **av)
{
    int index = 0;
    while (index < 10)
    {
        test_for_loop();
        index += 1;
    }

    return 0;
} 