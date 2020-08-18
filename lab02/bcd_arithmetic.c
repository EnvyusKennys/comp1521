#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number
// bcd points to an array of size n_bcd
// each array element contains 1 decimal digit
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

big_bcd_t *expression(char ***tokens);
big_bcd_t *term(char ***tokens);

int main(int argc, char *argv[]) {
    char **tokens = argv + 1;

    // tokens points in turn to each of the elements of argv
    // as the expression is evaluated.

    if (*tokens) {
        big_bcd_t *result = expression(&tokens);
        bcd_print(result);
        printf("\n");
        bcd_free(result);
    }

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {
    // PUT YOUR CODE HERE
    int num1 = x->n_bcd;
    int num2 = y->n_bcd;
    int space;
    int result;
    // find the one has most number, create a new array with the same size
    if (num1 > num2){
        space = num1;
    } else {
        space = num2;
    }

    big_bcd_t *sum = malloc(sizeof(big_bcd_t));
    sum->n_bcd = space;
    sum->bcd = malloc(sizeof(char)*space);
    for (int i = 0;i < space;i++){
        sum->bcd[i] = 0;
    } // set all value 0

    if (num1 != num2) {  // set length to the same for summing up
        if (space == num1){
            y->n_bcd = space;
            y->bcd= realloc(y->bcd,space);
            int i = num2;
            while (i < space){
                y->bcd[i] = 0;
                i++;
            }
        } else {
            x->n_bcd = space;
            x->bcd = realloc(x->bcd,space);
            int i = num1;
            while (i < space){
                x->bcd[i] = 0;
                i++;
            }
        }
    }
    int carry = 0;
    for (int i = 0;i < space;i++){
        result = x->bcd[i] + y->bcd[i] + carry;
        if (result < 10){
             sum->bcd[i] = result;
             carry = 0;
        }
        else {
            result = result % 10;
            sum->bcd[i] = result;
            carry = 1;
        }
    }
    // check if one more carry is needed
    if (carry == 1){
        sum->bcd = realloc(sum->bcd,space + 1);
        sum->n_bcd++;
        sum->bcd[space] = 1;
    }

    return sum;
}

big_bcd_t *bcd_subtract(big_bcd_t *x, big_bcd_t *y) {
    // PUT YOUR CODE HERE
    int num1 = x->n_bcd;
    int num2 = y->n_bcd;
    int space;
    int result;
    // find the one has most number, create a new array with the same size
    if (num1 > num2){
        space = num1;
    } else {
        space = num2;
    }

    big_bcd_t *subtract = malloc(sizeof(big_bcd_t));
    subtract->n_bcd = space;
    subtract->bcd = malloc(sizeof(char)*space);
    for (int i = 0;i < space;i++){
        subtract->bcd[i] = 0;
    } // set all value 0

    if (num1 != num2) {  // set length to the same for subtracting up
        if (space == num1){
            y->n_bcd = space;
            y->bcd= realloc(y->bcd,space);
            int i = num2;
            while (i < space){
                y->bcd[i] = 0;
                i++;
            }
        } else {
            x->n_bcd = space;
            x->bcd = realloc(x->bcd,space);
            int i = num1;
            while (i < space){
                x->bcd[i] = 0;
                i++;
            }
        }
    }
    int borrow = 0;
    for (int i = 0;i < space;i++){
        result = x->bcd[i] - y->bcd[i] - borrow;
        if (result > 0){
             subtract->bcd[i] = result;
             borrow = 0;
        }
        else {
            if (i == space - 1){}else {
                result = -result;
            } 
            subtract->bcd[i] = result;
            borrow = 1;
        }
    }

    return subtract;
}

big_bcd_t *bcd_multiply(big_bcd_t *x, big_bcd_t *y) {
    // PUT YOUR CODE HERE
    return NULL;
}

big_bcd_t *bcd_divide(big_bcd_t *x, big_bcd_t *y) {
    // PUT YOUR CODE HERE
    return NULL;
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_arithmetic is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}


// DO NOT CHANGE THE CODE BELOW HERE

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_arithmetic is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}


// simple recursive descent evaluator for  big_bcd_t expressions
big_bcd_t *expression(char ***tokens) {

    big_bcd_t *left = term(tokens);
    assert(left);

    if (!**tokens|| (***tokens != '+' && ***tokens != '-')) {
        return left;
    }

    char *operator = **tokens;
    (*tokens)++;

    big_bcd_t *right = expression(tokens);
    assert(right);

    big_bcd_t *result;
    if (operator[0] == '+') {
        result = bcd_add(left, right);
    } else {
        assert(operator[0] == '-');
        result = bcd_subtract(left, right);
    }
    assert(result);

    bcd_free(left);
    bcd_free(right);
    return result;
}


// evaluate a term of a big_bcd_t expression
big_bcd_t *term(char ***tokens) {

    big_bcd_t *left = bcd_from_string(**tokens);
    assert(left);
    (*tokens)++;

    if (!**tokens || (***tokens != '*' && ***tokens != '/')) {
        return left;
    }

    char *operator = **tokens;
    (*tokens)++;

    big_bcd_t *right = term(tokens);
    assert(right);

    big_bcd_t *result;
    if (operator[0] == '*') {
        result = bcd_multiply(left, right);
    } else {
        result = bcd_divide(left, right);
    }
    assert(result);

    bcd_free(left);
    bcd_free(right);
    return result;
}
