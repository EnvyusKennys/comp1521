#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // PUT YOUR CODE HERE
    uint32_t result = 0;
    uint32_t mask = 0xF; // 0000 .... 1111
    
    // byte represent on digit
    for (int i = 0; i <= 7; i++){
        int temp = (packed_bcd_value & mask) >> (4 * i);
        // result = result + temp * (10 ^ i);
        if (temp != 0){
            uint32_t tenth = 1;
            for (int j = 0; j < i; j++){
                tenth *= 10;
            }
            result = result + temp * tenth;
            
        }
        mask = mask << 4;
    }
    
    return result;
}
