 #include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick


int main(void)
{
    test_monocore_string();
    // test_monocore_large_class();
    // test_monocore_string();
    // printf("siseof int : %i\n", sizeof(int));
    // printf("siseof addr_t : %i\n", sizeof(addr_t));
    // printf("siseof radix_t : %i\n", sizeof(radix_t));
    // printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    // create_mem_handler();
    // void* ptr = NULL;
    // void* ptr_2 = NULL;
    // int index = 0;
    // // while (index < 276)
    // // {
    // //     test_for_loop();
    // //     index += 1;
    // // }
    // ptr = malloc(12);
    // free(ptr);
    // printf("\n");
    // while (index < 256)
    // {
    //     if (index == 240)
    //     {
    //         ptr_2 = ptr;
    //     }
    //     ptr = test_for_loop_02();
    //     index += 1;
    // }
    // while (index < 260)
    // {
    //     test_for_loop_02();
    //     index += 1;
    // }
    // my_free(ptr);
    // my_free(ptr_2);
    // while (index < 270)
    // {
    //     ptr = test_for_loop_02();
    //     index += 1;
    // }
    // my_free(ptr);
    return EXIT_SUCCESS;
}