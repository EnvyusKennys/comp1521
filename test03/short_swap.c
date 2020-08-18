// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value)
{
    // PUT YOUR CODE HERE
    uint16_t result;
    uint16_t mask = 0xff;
    uint16_t mask2 = 0xff00;
    result = (mask2 & value) >> 8;
    result = result | ((mask & value) << 8);
    return result;
}
