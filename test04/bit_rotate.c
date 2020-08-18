#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits)
{
    uint16_t result = bits;
    uint16_t mask = 1u << 15;
    uint16_t mask2 = 1;
    if (n_rotations > 0)
    {
        for (int i = 0; i < n_rotations; i++)
        {
            if ((result & mask) == mask)
            {
                result = result << 1;
                result++;
                continue;
            }
            result = result << 1;
        }
    }
    else
    {
        for (int i = 0; i > n_rotations; i--)
        {
            if ((result & mask2) == mask2)
            {
                result = result >> 1;
                result = result | mask;
                continue;
            }
            result = result >> 1;
        }
    }
    return result; //REPLACE ME WITH YOUR CODE
}
