// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value)
{
    // PUT YOUR CODE HERE
    uint64_t result = 0;
    uint64_t mask = 1;
    for (int i = 0; i < 32; i++)
    {
        result = result | ((mask & value) << 1);
        mask = mask << 1;
        result = result | ((mask & value) >> 1);
        mask = mask << 1;
    }
    return result;
}
