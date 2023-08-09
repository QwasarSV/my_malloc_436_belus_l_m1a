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

int loop_test_addr_retrieval()
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
            count += test_addr_retrieval(index, jndex);
            jndex += 1;
            total_test += 1;
        }
        jndex = 0;
        index += 1;
    }
    count = total_test - count;
    printf("Test passed : %i/%i\n", count, total_test);
    printf("TESTING RADIX TREE END...\n\n\n");
}

int test_addr_retrieval(int spacing, int class)
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
    void* test_run_start = find_run_start(arena->root, (void*)addr + mod);
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
    void* run_start = find_run_start(arena->root, dest_01);
    if (run_start) {
        printf("The run start for address %p is %p\n", dest_01, run_start);
    } else {
        printf("No run start found for address %p\n", dest_01);
    }
}

void test_for_loop_02()
{
    int size_tracker = 0;
    char* src = "hello this is a string probleme or maybe a struct issue 123456789";
    size_tracker += my_strlen(src) + 1;
    printf("string size is : %i\n", my_strlen(src)+1);
    char* dest_01 = req_slot(my_strlen(src) + 1);
    printf("total used size is :%i\n", size_tracker);
    my_strcpy(dest_01, src);
    printf("%s\n", dest_01);
    void* run_start = find_run_start(arena->root, (void*)dest_01);
    if (run_start) {
        printf("The run start for address %p is %p\n", dest_01, run_start);
    } else {
        printf("No run start found for address %p\n", dest_01);
    }
}