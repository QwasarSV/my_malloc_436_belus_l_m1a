#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick

// #define PAGE_SIZE 16384

// void maps_run_on_radix_tree();

// arena_t* arena;


// void create_tcache(void* addr);

//total tcache size per thread = nb_bin * run_size + arena_metadata;







int main(void)
{
    // printf("siseof int : %i\n", sizeof(int));
    // printf("siseof addr_t : %i\n", sizeof(addr_t));
    // printf("siseof radix_t : %i\n", sizeof(radix_t));
    new_run_batch();
    
    int index = 0;
    while (index < 10)
    {
        test_for_loop();
        index += 1;
    }
    printf("\n");
    while (index < 20)
    {
        test_for_loop_02();
        index += 1;
    }

    return EXIT_SUCCESS;
}