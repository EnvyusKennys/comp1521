// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"
// separate out the 3 components of a float
float_components_t float_bits(uint32_t f)
{
    // PUT YOUR CODE HERE
    float_components_t x;
    uint32_t sign_mask = 1u << 31;
    uint32_t exp_mask = 255 << 23;
    uint32_t frac_mask = (1 << 23) - 1;
    x.sign = (f & sign_mask) >> 31;
    x.exponent = (f & exp_mask) >> 23;
    x.fraction = f & frac_mask;

    return x;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f)
{
    // PUT YOUR CODE HERE
    // check if exp is all 1
    int mask = 1;
    for (int i = 0; i < 8; i++)
    {
        if (f.exponent & mask)
        {
        }
        else
        {
            return 0;
        }
        mask = mask << 1;
    }

    // check if fraction is non-zero
    mask = 1;
    for (int i = 0; i < 23; i++)
    {
        if (f.fraction & mask)
        {
            return 1;
        }
        mask = mask << 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f)
{
    // PUT YOUR CODE HERE
    int mask = 1;
    if (f.sign == 0)
    {
        // check if exponent is 11111111
        for (int i = 0; i < 8; i++)
        {
            if (f.exponent & mask)
            {
            }
            else
            {
                return 0;
            }
            mask = mask << 1;
        }
        // check if fraction is 0
        if (f.fraction == 0)
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f)
{
    // PUT YOUR CODE HERE
    int mask = 1;
    if (f.sign == 1)
    {
        // check if exponent is 11111111
        for (int i = 0; i < 8; i++)
        {
            if (f.exponent & mask)
            {
            }
            else
            {
                return 0;
            }
            mask = mask << 1;
        }
        // check if fraction is 0
        if (f.fraction == 0)
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f)
{
    // PUT YOUR CODE HERE
    if (f.fraction == 0 && f.exponent == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f)
{
    // PUT YOUR CODE HERE
    float_components_t new = float_bits(f);

    if (is_nan(new) | is_negative_infinity(new) | is_positive_infinity(new) | is_zero(new))
    {
        return f;
    }
    uint32_t result = (new.sign << 31);
    if ((new.exponent + 11) <= 0xff)
    {
        new.exponent = (new.exponent + 11) << 23;
    }
    else
    {
        new.exponent = 0xff << 23;
        new.fraction = 0;
    }
    result = result | new.exponent;
    result = result | new.fraction;
    return result;
}
