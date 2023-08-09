#include <main_header.h>

radix_t* memory_segment;
radix_t* free_chunck = NULL;

void init_memory_segment(void* mem_seg, size_t elem_cnt)
{
    memory_segment = (radix_t*)mem_seg;
    for (int index = 0; index < elem_cnt - 1; index++)
    {
        memory_segment[index].right = &memory_segment[index + 1];
    }
    memory_segment[elem_cnt - 1].right = NULL;

    free_chunck = &memory_segment[0];
}

radix_t* allocate_node()
{
    if (!free_chunck)
    {
        // write(STDERR_FILENO, MEM_segment_SPACE, SIZE_MSG_SPACE);
        return NULL;
    }

    radix_t* node = free_chunck;
    free_chunck = free_chunck->right;
    return node;
}

// void destroy_memory_segment()
// {
//     free(memory_segment);
// }
