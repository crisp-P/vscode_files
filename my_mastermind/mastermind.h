#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <stdio.h>
#include <stdbool.h>

typedef struct integer_array {

    int size;
    int array[4];

}integer_array;

void generating_code(integer_array *code);
bool verification_test(int code, int size);

#endif

