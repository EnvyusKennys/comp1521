// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i)
{
    uint32_t addi_m = 0x20000000;
    uint32_t i_m = 0xffff;
    uint32_t result = addi_m + (s << 21) + (t << 16) + (i & i_m);
    return result; // REPLACE WITH YOUR CODE
}
