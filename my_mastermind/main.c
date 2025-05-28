// main.c
#include "mastermind.h"
#include <stdlib.h>
#include <unistd.h>

int get_user_input(char user_input[100], int *size);

int main(int ac, char **av) {

    integer_array code = {4, {1,1,1,1}};
    int size = 0;
    char user_input[100];
    int attempts = 10;

    //generating_random_code(&code);//ye this generates a random number and puts it into a int array. of size 4.
    attempts = parameters(av, ac, &code, attempts);
/////////// this is a test funtction to print out generated code
    for(int i = 0; i < code.size; i++) {
        printf("%d", code.array[i]);
    }
    printf("\n");
///////////
    
    while(attempts > 0) {
        
        attempts--;

        if(get_user_input(user_input, &size) == -1) {
            return 1;
        }
        while(valid_user_input(user_input, size) == false) {//valid user grabs what was read from stdin user_input thats why we need to also pass size so we dont read random data only what was inputed by user.

            if(get_user_input(user_input, &size) == -1) {
                return 1;
            }
        }
        printf("attempts %d\n", attempts);
        if(checking_piece_placements(&code, user_input) == true) {
            printf("congrats and shit\n");
            return 0;
        }
        
    }    


    printf("better luck next time btw the code was %s\n", code.array);

    return 0;
}

int get_user_input(char user_input[100], int *size) {// this function is used to make it more clear what im doing it checks to see also if user inputed ctrl+z

    *size = read(0, user_input, 100) - 1;

    return *size;

}