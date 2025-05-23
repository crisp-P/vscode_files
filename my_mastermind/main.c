// main.c
#include "mastermind.h"
#include <stdlib.h>
#include <unistd.h>

int main() {

    integer_array code = {4, {1,1,1,1}};
    char buffer[100];

    generating_code(&code);
    
    for(int i = 0; i < 4; i++) {
        printf("%d", code.array[i]);
    }
    printf("\n");

   int size = read(0, buffer, 100) - 1;
    
    while(!verification_test(atoi(buffer), size)) {
        size = read(0, buffer, 100) - 1;
    }
    printf("inputed code == %d\n", atoi(buffer));

    return 0;
}