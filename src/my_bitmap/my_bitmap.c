#include <main_header.h>

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

void clear_bit(bmp_t* bmp, int index)
{
    bmp->data &= ~(1 << index);
}

int get_bit(bmp_t bmp, int index)
{
    return (bmp.data >> index) & 1;
}

void set_in_bmp(run_t* run, int index, int value)
{
    int bmp_index = index / 8;
    int bit_index = index % 8;

    set_bit(&run->bmp[bmp_index], bit_index, value);
}

void clear_in_bmp(run_t* run, int index)
{
    int bmp_index = index / 8;
    int bit_index = index % 8;

    clear_bit(&run->bmp[bmp_index], bit_index);
}

int get_from_bmp(run_t* run, int index)
{
    int bmp_index = index / 8;
    int bit_index = index % 8;

    return get_bit(run->bmp[bmp_index], bit_index);
}

int find_free_slot(run_t* run)
{
    int byte_index = run->last_known_free_position / 8;
    int bit_index = 0;
    int result = 0;
    while (byte_index < BITMAP_SIZE)
    {
        while (bit_index < 8)
        {
            if (!get_bit(run->bmp[byte_index], bit_index))
            {
                result = byte_index * 8 + bit_index;
                run->last_known_free_position = result;
                return result;
            }
            bit_index += 1;
        }
        bit_index = 0;
        byte_index += 1;
    }
    return -1;
}

bool is_bitmap_full(run_t* run)
{
    int index = 0;
    while (index < BITMAP_SIZE)
    {
        if (run->bmp[index].data != 0xFF)
        {
            return false;
        }
        index += 1;
    }
    return true;
}

void set_bitmap(run_t* run)
{
    int index = 0;
    while (index < BITMAP_SIZE)
    {
        run->bmp[index].data =  0x00;
        index += 1;
    }
}



int test_bitmap()
{
    bmp_t bmp = {0};

    set_bit(&bmp, 3, 1);
    printf("Bit at index 3: %d\n", get_bit(bmp, 3));
    
    clear_bit(&bmp, 3);
    printf("Bit at index 3: %d\n", get_bit(bmp, 3));
    return EXIT_SUCCESS;
}