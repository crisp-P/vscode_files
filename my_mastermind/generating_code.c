#include "mastermind.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

bool checks_not_legal(integer_array *code , int i);

void generating_code(integer_array *code) {
    
    srand(time(NULL));

    for (int i = 0; i < code->size; i++) {
        code->array[i] = rand() % 9;
        //printf("%d\n", code->array[i]);
        while(checks_not_legal(code, i)) {
            code->array[i] = rand() % 9;
            //printf("did it change? = %d\n", code->array[i]);
        }

    }
}


bool checks_not_legal(integer_array *code , int i) {
    for (int j = i - 1; j >= 0; j--) {

        if (code->array[j] == code->array[i]) {

            return true;
        }
    }
    return false;
}
