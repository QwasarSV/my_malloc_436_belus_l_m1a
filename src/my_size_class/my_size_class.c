#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick

int spacing_values[SPACING_COUNT] = {
    SPACING_8,
    SPACING_16,
    SPACING_32,
    SPACING_64,
    SPACING_128,
    SPACING_256,
    SPACING_512,
    SPACING_1024,
    SPACING_2048
};

int size_class[SPACING_COUNT][9] = {
    {8, 0},
    {16, 32, 48, 64, 80, 96, 112, 128, 0},
    {160, 192, 224, 256, 0},
    {320, 384, 448, 512, 0},
    {640, 768, 896, 1024, 0},
    {1280, 1536, 1792, 2048, 0},
    {2560, 3072, 3584, 4096, 0},
    {5120, 6144, 7168, 8192, 0},
    {10240, 12288, 14336, 0}
};

int nearest_spacing_index(size_t size_request)
{
    int left = 0;
    int right = SPACING_COUNT - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (spacing_values[mid] == size_request)
        {
            return mid;
        }
        if (spacing_values[mid] < size_request)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left;
}

int get_size_class_index(int class_index, size_t size)
{
    int index = 0;
    while (size_class[class_index][index] != 0)
    {
        if (size_class[class_index][index] >= size)
        {
            return index;
        }
        index += 1;
    }
    return -1;
}

// test and build functions/
int binary_search(int array[], int left, int right, int value) 
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;
        if (array[mid] == value)
        {
            return mid;
        }
  
        if (array[mid] > value)
        {
            return binary_search(array, left, mid - 1, value);
        }
        else
        {
            return binary_search(array, mid + 1, right, value);
        }
    }
    return -1;
}

int nearest_spacing(size_t size_request)
{
    int left = 0;
    int right = SPACING_COUNT - 1;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (spacing_values[mid] == size_request)
        {
            return spacing_values[mid];
        }
        if (spacing_values[mid] < size_request)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return spacing_values[left];
}

int get_spacing_index(int value)
{
    return binary_search(spacing_values, 0, SPACING_COUNT - 1, value);
}

int get_size_class(int class_index, size_t size)
{
    int index = 0;
    while (size_class[class_index][index] != 0)
    {
        if (size_class[class_index][index] >= size)
        {
            return size_class[class_index][index];
        }
        index += 1;
    }
    return -1;
}

void test_class_retrieval_system(int size_req)
{
    printf("search for size_class match: %i \n", size_req);
    int nearest_spacing_val = nearest_spacing(size_req);

    printf("The nearest spacing, %i\n", nearest_spacing_val);
    
    int spacing_index = get_spacing_index(nearest_spacing_val);
    printf("the spacing index, %i\n", spacing_index);
    
    int size_class_value = get_size_class(spacing_index, size_req);
    printf("ouput_size_class, %i\n", size_class_value);
}