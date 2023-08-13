#ifndef __MY_TEST_HEADER_FILE_
#define __MY_TEST_HEADER_FILE_

#include <main_header.h>

void    test_class_retrieval_system(int size_req);
int     test_binmap(int size_req);
int     test_bitmap();
int     test_routine(void);
int     loop_test_addr_retrieval(arena_t* arena);
int     test_addr_retrieval(arena_t* arena, int spacing, int class);
void    test_for_loop();
void    test_for_loop_02();

#endif