#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f)
{
    uint32_t result = 0x0;
    uint64_t mask = 1u << 31;
    uint64_t mask2 = (1u << 31) - 1;
    result = f & mask2;
    result = result | ((~(f & mask) >> 31) << 31);
    return result; // REPLACE ME WITH YOUR CODE
}
