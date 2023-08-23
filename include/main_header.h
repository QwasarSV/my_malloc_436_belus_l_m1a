#ifndef __MAIN_HEADERFILE_
#define __MAIN_HEADERFILE_
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdint.h>

#include <my_libasm.h>

#include <non_standard_header.h>
#include <my_string.h>
#include <my_readline.h>
#include <my_parser.h>
#include <my_hash.h>
#include <my_set.h>
#include <my_stdio.h>


#include <my_error_handler.h>
#include <my_size_class.h>
#include <my_binmap.h>
#include <my_arena.h>

#include <my_mem_pool.h>
#include <my_bitmap.h>
#include <my_run.h>
#include <my_tcache.h>
#include <my_allocator.h>
#include <my_linkedlist.h>
#include <my_jemalloc.h>

#include <test_fn_header_file.h>

#endif