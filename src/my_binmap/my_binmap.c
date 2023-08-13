#include <main_header.h>

// https://stackoverflow.com/questions/426230/what-is-the-ld-preload-trick


// bool binmap[SPACING_COUNT][9] = {true};


bool is_size_class_free(int spacing, int size_class_index, binmap_t* binmap)
{
    return binmap->data[spacing][size_class_index];
}

int mark_size_class(int spacing, int size_class_index, binmap_t* binmap)
{
    if (spacing > SPACING_COUNT -1)
    {
        // "ERR_SIZE_CLASS : size_class_does not belong"
        return EXIT_FAILURE;
    }
    binmap->data[spacing][size_class_index] = false;
    return EXIT_SUCCESS;
}

int free_size_class(int spacing, int size_class_index, binmap_t* binmap)
{
    if (spacing > SPACING_COUNT -1)
    {
        // "ERR_SIZE_CLASS : size_class_does not belong"
        return EXIT_FAILURE;
    }
    binmap->data[spacing][size_class_index] = true;
    return EXIT_SUCCESS;
}

binmap_t create_binmap()
{
    binmap_t binmap = {.data = {true}};
    return binmap;
}

int test_binmap(int size_req)
{
    printf("Finding binmap relative to size : %i\n", size_req);
    int spacing_index = nearest_spacing_index(size_req);
    printf("Spacing index : %i\n", spacing_index);

    int class_index = get_size_class_index(spacing_index, size_req);
    printf("Class index : %i\n", class_index);

    printf("creating binmap");
    binmap_t binmap = create_binmap();
    printf("Requesting bin map for size_class %i\n", size_class[spacing_index][class_index]);

    printf("Marking class\n");
    mark_size_class(spacing_index, class_index, &binmap);
    printf("Class avalaiblity is : %i\n", is_size_class_free(spacing_index, class_index, &binmap));

    printf("Freeing class\n");
    free_size_class(spacing_index, class_index, &binmap);
    printf("Class avalaiblity is : %i\n", is_size_class_free(spacing_index, class_index, &binmap));

    return EXIT_SUCCESS;
}

