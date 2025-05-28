#include "mastermind.h"
#include <stdio.h>
//this code needs a int array and a string array for it to work
//the int array is the struct integer_array the string array would be the user code.
bool checking_piece_placements(integer_array *secret_code, char user_code[4]) {
    int misplace_pieces = 0;
    int matching_pieces = 0;
    for(int i = 0; i < secret_code->size; i++) {
        for(int j = 0; j < 4; j++) {
            if(secret_code->array[i] == user_code[j] - '0' && i == j) {
                matching_pieces++;

            }else if(secret_code->array[i] == user_code[j] - '0') {
                misplace_pieces++;
            }
        }
    }
    printf("misplaced pieces = %d\n",misplace_pieces);
    printf("matching pieces = %d\n",matching_pieces);
    if(matching_pieces == 4) {
        return true;
    }
    
    return false;
}