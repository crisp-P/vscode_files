#include "mastermind.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void fill_code(char string[], integer_array *code);

int parameters (char **av, int ac, integer_array *code, int attempts) {
    bool was_c_called = false;// this just to check and see if parameter c exists
    attempts = 10;
    for(int i = 0; i < ac; i++) {//just looping through the char **array

        if(av[i][0] == '-' && av[i][1] != '\0' || av[i][1] == ' ') {//this checks to see if first letter is - following with some value thats not space or null tho i dont think i need that the check for space or null.
            
            for(int j = 0; av[i][j] != '\0'; j++) {//this checks for parameters and also checks to see if they filled out infomation needed for it.
                if(av[i][j] == 't' && i + j < ac) {

                    //printf("attempts == %d i + j = %d\n", atoi(av[j + i]), i + j);
                    //printf("attempts are == %d\n", attempts);
                    attempts = atoi(av[j + i]);
                    //printf("attempts are set to == %d\n", attempts);
                    if(attempts == 0) {
                        attempts = 10;
                    }

                }
                if(av[i][j] == 'c' && i + j < ac) {
                    //printf("in c\n");
                    was_c_called = true;

                    if(valid_user_input(av[i + j] , strlen(av[i + j])) == true) {
                        fill_code(av[i + j], code);
                    }else{
                        generating_random_code(code);
                    }
                }
            }
            

        }
    }

    if(was_c_called == false) {
        //printf("in c == false\n");
        generating_random_code(code);
    }
    printf("attempts are == %d\n", attempts);
    return attempts;
}


void fill_code (char string[], integer_array *code) {
    for(int i = 0; i < code->size; i++) {
        code->array[i] = string[i] - '0';
    }
}