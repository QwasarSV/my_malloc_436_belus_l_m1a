#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick


int main(void)
{
    // printf("siseof int : %i\n", sizeof(int));
    // printf("siseof addr_t : %i\n", sizeof(addr_t));
    // printf("siseof radix_t : %i\n", sizeof(radix_t));
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    create_mem_handler();

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