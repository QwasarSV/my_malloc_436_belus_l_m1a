#include <main_header.h>


int test_routine(void)
{
    int size_run = sizeof(run_t);
    int size_run_ptr = sizeof(run_t*);
    printf("sizeof(run) %i \n", size_run);
    printf("sizeof(run*) %i\n", size_run_ptr);
    printf("testing class retrieval :\n");
    test_class_retrieval_system(256);
    test_class_retrieval_system(257);
    test_class_retrieval_system(10);
    test_class_retrieval_system(500);
    test_class_retrieval_system(2043);
    test_class_retrieval_system(13500);

    printf("\n\n\ntesting binmap system :\n");
    test_binmap(10);
    test_binmap(5000);
    test_binmap(25);
    test_binmap(128);
    return EXIT_SUCCESS;
}

int loop_test_addr_retrieval(arena_t* arena)
{
    int index = 0;
    int jndex = 0;
    int count = 0;
    int total_test = 0;
    printf("TESTING RADIX TREE :\n\n\n");
    printf("size of run_t :%lu\n", sizeof(run_t));
    while (index < SPACING_COUNT -1)
    {
        while (size_class[index][jndex] != 0)
        {
            count += test_addr_retrieval(arena, index, jndex);
            jndex += 1;
            total_test += 1;
        }
        jndex = 0;
        index += 1;
    }
    count = total_test - count;
    printf("Test passed : %i/%i\n", count, total_test);
    printf("TESTING RADIX TREE END...\n\n\n");
    return EXIT_SUCCESS;
}

int test_addr_retrieval(arena_t* arena, int spacing, int class)
{
    int mult = 1044;
    int mod = 0;
    int index = 0;
    void* addr = arena->_tcache_[spacing][class].address;
    printf("Testing batch on size_class(%i) at starting addr: (%p)\n", size_class[spacing][class], (void*)addr);
    while (index < 3)
    {
    mod = index * mult;
    printf("Looking start of : %p\n", (void*)addr + mod);
    void* test_run_start = find_run_start(handler->root, (void*)addr + mod);
    printf("Found run start at: %p/%p\n\n", test_run_start, arena->_tcache_[spacing][class].address);
    index += 1;
        if ((uintptr_t)test_run_start != (uintptr_t)addr)
        {
            printf("EXIT_FAILURE /!\\");
            return EXIT_FAILURE;
        }
    }
    printf("End of batch\n\n");
    return EXIT_SUCCESS;
}

void test_for_loop()
{
    int size_tracker = 0;
    char* src = "hello this is a string probleme or maybe a struct issue 1234567";
    size_tracker += my_strlen(src) + 1;
    printf("string size is : %i\n", my_strlen(src)+1);
    char* dest_01 = req_slot(my_strlen(src) + 1);
    printf("total used size is :%i\n", size_tracker);
    my_strcpy(dest_01, src);
    printf("%s\n", dest_01);
    void* run_start = find_run_start(handler->root, dest_01);
    if (run_start)
    {
        printf("The run start for address %p is %p\n", dest_01, run_start);
    } 
    else
    {
        printf("No run start found for address %p\n", dest_01);
    }
}

void* test_for_loop_02()
{
    int size_tracker = 0;
    char* src = "hello";
    size_tracker += my_strlen(src) + 1;
    printf("string size is : %i\n", my_strlen(src)+1);
    char* dest_01 = req_slot(my_strlen(src) + 1);
    printf("total used size is :%i\n", size_tracker);
    my_strcpy(dest_01, src);
    printf("%s\n", dest_01);
    void* run_start = find_run_start(handler->root, (void*)dest_01);
    if (run_start)
    {
        printf("The run start for address %p is %p\n", dest_01, run_start);
    }
    else
    {
        printf("No run start found for address %p\n", dest_01);
    }
    return (void*)dest_01;
}

#ifndef PTR_LIST_S
#define PTR_LIST_S
struct ptr_list_s
{
    int size_byte;
    void* ptr;
    struct ptr_list_s* next;
};
typedef struct ptr_list_s ptr_l_t;
#endif

#ifndef _TEST_STRUCT_
#define _TEST_STRUCT_
struct test_struct
{
    int     member_01;
    char*   member_02;
    void*   member_03;
};
typedef struct test_struct test_t;
#endif

ptr_l_t* create_new_test_node(void* address)
{
    ptr_l_t* new_node = my_malloc(sizeof(ptr_l_t));
    new_node->ptr = address;
    new_node->next = NULL;
    return new_node;
}

void insert_test_node_at_head(ptr_l_t** head, ptr_l_t* node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}


void is_test_string_comform(char* test_str, char* stored_str)
{
    if (my_strcmp(test_str, stored_str) != 0)
    {
        printf("CANNOT RETRIEVE STRING\n");
        exit(0);
    }
}

void free_ptr_list(ptr_l_t* head, char* test_str)
{
    ptr_l_t* tmp = NULL;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        is_test_string_comform(test_str, (char*)tmp->ptr);
        // printf("string: %s\n", (char*)tmp->ptr);
        my_free(tmp->ptr);
        my_free(tmp);
    }
}


void check_ptr_list(ptr_l_t* head, char* test_str)
{
    ptr_l_t* tmp = head;
    while (tmp != NULL)
    {
        is_test_string_comform(test_str, (char*)tmp->ptr);
        // printf("string: %s\n", (char*)tmp->ptr);
        tmp = tmp->next;
    }
}

char* alloc_and_cpy(char* src)
{
    int     len  = my_strlen(src);
    char*   dest = my_malloc(len + 1);
    my_strcpy(dest, src);
    return dest;
}

int my_je_malloc_test_01(ptr_l_t** head, char* src, int cycles)
{
    ptr_l_t* tmp    = NULL;
    void*    ptr    = NULL;
    int      index  = 0;
    // char*    src    = "this is a test_string!";

    while (index < cycles)
    {
        ptr = (void*)alloc_and_cpy(src);
        tmp = create_new_test_node((void*) ptr);
        insert_test_node_at_head(head, tmp);
        index += 1;
    }
    // free_ptr_list(head, src);
    return EXIT_SUCCESS;
}


int test_monocore_string()
{
    ptr_l_t* head   = NULL;
    char*    src1   = "hello world";
    my_je_malloc_test_01(&head, src1, 204500);
    free_ptr_list(head, src1);
    // check_ptr_list(head, src1);
    head = NULL;
    return EXIT_SUCCESS;
}

void loop_large_class()
{
    void* ptr = my_malloc(35540);
    char* src1 = "hello world";
    my_strcpy((char*)ptr, src1);
    printf("string:%s\n",(char*)ptr);
    // printf("Finding adress at :%p\n", find_run_start(handler->root, (void*)ptr));
    my_free(ptr);
}

int test_monocore_large_class()
{   
    int index = 0;
    while (index < 10)
    {
        loop_large_class();
        index += 1;
    }   
    return EXIT_SUCCESS;
}