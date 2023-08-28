#include <main_header.h>

void insert_bmp(bitlist_t** head, bitlist_t* node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
}

void set_bitmap(bmp_t* bmp)
{
    int index = 0;
    while (index < BITMAP_SIZE)
    {
        bmp[index].data =  0x00;
        index += 1;
    }
}

void set_bit(bmp_t* bmp, int index, int value)
{
    if (value)
    {
        bmp->data |= (1 << index);
    }
    else
    {
        bmp->data &= ~(1 << index);
    }
}

bool is_bitmap_full(bitlist_t* node)
{
    int start_offset = calc_nb_slot(sizeof(bitlist_t) + sizeof(bitlist_t) + sizeof(page_t), node->nb_page);
    int index = start_offset;
    while (index < BITMAP_SIZE)
    {
        if (node->bmp[index].data != 0xFF)
        {
            return false;
        }
        index += 1;
    }
    return true;
}

void set_in_bmp(bmp_t* bmp, int index, int value)
{
    int bmp_index = index / 8;
    int bit_index = index % 8;

    set_bit(&bmp[bmp_index], bit_index, value);
}

void set_bits(bmp_t* bmp, int start, int len, int value)
{
    int index = 0;
    while ( index < len)
    {
        set_in_bmp(bmp, start + index, value);
        index += 1;
    }
}

/* #################### count_free_bits ###################
    count the nomber of free slots from a given position.
    @return (int) Number of available slots
*/
void initialize_bit_list(void* ptr, int nb_page)
{
    bitlist_t* new_node = (bitlist_t*)ptr;

    int index = 0;
    while (index < BITMAP_SIZE)
    {
        new_node->bmp[index].data =  0x00;
        index += 1;
    }
    new_node->nb_page = nb_page; 
    new_node->next = NULL;
    int len = calc_nb_slot(sizeof(bitlist_t) + sizeof(bitlist_t) + sizeof(page_t), new_node->nb_page);
    set_bits(new_node->bmp, 0, len, true);
    // printf("insert_new_BMP\n");
    insert_bmp(&handler->head, new_node);  
}

int get_bit(bmp_t bmp, int index)
{
    return (bmp.data >> index) & 1;
}


/* #################### count_free_bits ###################
    count the nomber of free slots from a given position.
    @return (int) Number of available slots
*/
int count_free_bits(bmp_t* bmp, int from, int len)
{
    int byte_index = from / 8;
    int bit_index = from % 8;
    int free_bits_count = 0;

    while (free_bits_count < len && byte_index < BITMAP_SIZE)
    {
        while (bit_index < 8 && free_bits_count < len)
        {
            if (!get_bit(bmp[byte_index], bit_index))
            {
                free_bits_count += 1;
                bit_index += 1;
            }
            else
            {
                return free_bits_count;
            }
        }

        if (free_bits_count < len)
        {
            byte_index += 1;
            bit_index = 0;
        }
    }

    return free_bits_count;
}

int find_free_slot(bmp_t* bmp, int len)
{
    int byte_index = 0;
    int bit_index = 0;
    int start = 0;
    int nb_slot = 0;
    while (byte_index < BITMAP_SIZE)
    {
        if (!get_bit(bmp[byte_index], bit_index))
        {
            start = byte_index * 8 + bit_index;
            if (start + len > BITMAP_SIZE * 8)
            {
                return -1;
            }
            nb_slot = count_free_bits(bmp, start, len);
            if (nb_slot >= len)
            {
                return start;
            }
            bit_index += nb_slot % 8;
            byte_index += nb_slot / 8;
            if (bit_index >= 8)
            {
                byte_index += bit_index / 8;
                bit_index %= 8;
            }
        }
        else
        {
            bit_index++;
        }

        if (bit_index >= 8)
        {
            bit_index = 0;
            byte_index++;
        }
    }
    return -1;
}


// // not optimized to recode
// // should have variable holding last free_position for quicker search
// // should have an actual algoritm to handle the search.
// /* #################### find_free_slot ###################
//     Roam through the bitlist to find an unused slot.
//     @return (int) free slot index
// */
// int find_free_slot(bmp_t* bmp, int len)
// {
//     int byte_index = 0;
//     int bit_index = 0;
//     int start = 0;
//     int nb_slot = 0;
//     while (byte_index < BITMAP_SIZE)
//     {
//         while (bit_index < 8)
//         {
//             if (!get_bit(bmp[byte_index], bit_index))
//             {
//                 start = byte_index * 8 + bit_index;
//                 if (start + len > BITMAP_SIZE* 8 -1)
//                 {
//                     return -1;
//                 }
//                 nb_slot = count_free_bits(bmp, start, len);
//                 if (nb_slot >= len)
//                 {
//                     return start;
//                 }
//                 bit_index += nb_slot % 8;
//                 byte_index += nb_slot / 8;
//               if (bit_index >= 8)
//               {
//                     byte_index += bit_index / 8;
//                     bit_index %= 8;
//               break;
//               }  
//             }
            
//             bit_index += 1;
//         }
//         bit_index = 0;
//         byte_index += 1;
//     }
//     // printf("returning -1\n");
//     return -1;
// }