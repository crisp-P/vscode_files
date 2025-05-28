#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <stdio.h>
#include <stdbool.h>

typedef struct integer_array {

    int size;
    int array[4];

}integer_array;

void generating_random_code(integer_array *code);
bool valid_user_input(char code[100], int size);
bool checking_piece_placements(integer_array *secret_code, char user_code[4]);
int parameters (char **av, int ac, integer_array *int_array, int attempts);

#endif

