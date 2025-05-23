#include "mastermind.h"
#include <stdlib.h>

bool verification_test(int code, int size) {

    
    int temp_aray[4];
    if(size != 4) {
        printf("error not legal input\n");
        return false;
    }

    for(int i = 0; i < 4; i++) {

        temp_aray[i] = code % 10;
        //printf("modulo buffer == %d\n", temp_aray[i] % 10);

        for(int j = i - 1; j >= 0; j--) {
            if(temp_aray[i] == temp_aray[j]) {
                printf("error not legal input\n");
                return false;
            }
        }
        code = code/10;
        
    }

    return true;

}