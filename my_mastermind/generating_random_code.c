#include "mastermind.h"
#include <time.h>
#include <stdlib.h>


bool checks_not_legal(integer_array *code , int i);

void generating_random_code(integer_array *code) {
    
    srand(time(NULL));

    for(int i = code->size - 1; i >= 0; i--) {
        code->array[i] = rand() % 9;
        //printf("%d\n", code->array[i]);

        while(checks_not_legal(code, i) == true) {//checks if current element equals any other elements
           code->array[i] = rand() % 9;
        }

    }

}


bool checks_not_legal(integer_array *code , int i) {

    for(int j = i; j < 3; j++) {//we set j to always look ahead of i so if i last element in array we skip this
        if(code->array[i] == code->array[j + 1]) {
            return true;
        }
    }

    return false;
}
