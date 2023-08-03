// #include <main_header.h>

// mseg_t* memory_segment;
// mseg_t* free_chunck;

// void init_memory_segment(int segment_size)
// {
//     memory_segment = (mseg_t*)my_mmap(segment_size);
//     if (!memory_segment)
//     {
//         write(STDERR_FILENO, MEM_segment_ALLOC, SIZE_MSG_ALLOC);
//         exit(EXIT_FAILURE);
//     }
//     for (int index = 0; index < segment_size - 1; index++)
//     {
//         memory_segment[index].next = &memory_segment[index + 1];
//     }
//     memory_segment[segment_size - 1].next = NULL;

//     free_chunck = &memory_segment[0];
// }

// mseg_t* allocate_cell()
// {
//     if (!free_chunck)
//     {
//         write(STDERR_FILENO, MEM_segment_SPACE, SIZE_MSG_SPACE);
//         return NULL;
//     }

//     mseg_t* cell = free_chunck;
//     free_chunck = free_chunck->next;
//     return cell;
// }

// void destroy_memory_segment()
// {
//     free(memory_segment);
// }
