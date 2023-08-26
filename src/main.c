#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick



int main(void)
{
    million_cycle_stress_test();
    // test_monocore_string();
    // test_monocore_large_class();
    printf("success !!\n");
} 