#ifndef __MY_SIZE_CLASS_
#define __MY_SIZE_CLASS_

#include <main_header.h>

#ifndef _SIZE_CLASS_DATA_
#define _SIZE_CLASS_DATA_

enum spacing {
    SPACING_8 = 8,
    SPACING_16 = 128,
    SPACING_32 = 256,
    SPACING_64 = 512,
    SPACING_128 = 1024,
    SPACING_256 = 2048,
    SPACING_512 = 4096,
    SPACING_1024 = 8192,
    SPACING_2048 = 14336,
    SPACING_COUNT = 10
};

extern int spacing_values[SPACING_COUNT];
extern int size_class[SPACING_COUNT][9];
#endif


int binary_search(int array[], int left, int right, int value);
int nearest_spacing(size_t size_request);
int get_class_index(int value);
int get_size_class(int class_index, size_t size);



#endif