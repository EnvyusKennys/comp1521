#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f)
{
    uint32_t mask = 255 << 23;
    uint32_t result = (f & mask) >> 23;
    return result; // REPLACE ME WITH YOUR CODE
}
