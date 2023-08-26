#include <main_header.h>

void insert_bmp(bmp_t** head, bmp_t* bmp_to_insert)
{
    bmp_to_insert->next = *head;
    *head = bmp_to_insert;
}

void set_bitmap(page_t* page)
{
    int index = 0;
    while (index < BITMAP_SIZE)
    {
        page->bmp[index].data =  0x00;
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

bool is_bitmap_full(bmp_t* bmp)
{
    int index = 0;
    while (index < BITMAP_SIZE)
    {
        if (bmp[index].data != 0xFF)
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

void initiate_bit_list(void* ptr, int nb_page)
{
  bmp_t* new_bmp = (bmp_t*)ptr;
  new_bmp->nb_page = nb_page;
  new_bmp->next = NULL;
  int index = 0;
  while (index < BITMAP_SIZE)
  {
    new_bmp[index].data =  0x00;
    index += 1;
  }
  int len = calc_nb_slot(sizeof(bmp_t)+ sizeof(page_t) , new_bmp->nb_page);
  set_bits(new_bmp, 0, len, true);
  // printf("insert_new_BMP\n");
  insert_bmp(&handler->head, new_bmp);  
}

int get_bit(bmp_t bmp, int index)
{
    return (bmp.data >> index) & 1;
}

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
        while (bit_index < 8)
        {
            if (!get_bit(bmp[byte_index], bit_index))
            {
                start = byte_index * 8 + bit_index;
                if (start + len > BITMAP_SIZE* 8 -1)
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
              break;
              }  
            }
            
            bit_index += 1;
        }
        bit_index = 0;
        byte_index += 1;
    }
    // printf("returning -1\n");
    return -1;
}