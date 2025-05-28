#include "mastermind.h"
#include <stdlib.h>

bool valid_user_input(char code[100], int size) {
    //printf("%d", size);
    if(size != 4) {
        return false;
    }

    for(int i = size - 1; i >= 0; i--) {

        if(code[i] < '0' || code[i] > '8') {// this checks to see if it really a number being passed
            return false;
        }
        for(int j = i + 1; j < size; j++) {
            //printf("array[i] = %c  array[j] = %c\n", code[i], code[j]); //this just test code see if everything working

            if(code[i] == code[j]) {// this checks for dups 
                return false;
            }
        }
    }

    return true;

}