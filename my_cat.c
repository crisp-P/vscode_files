#include <stdio.h>


int main(int ac, char **av) {
    
    FILE *file_pointer_read;
    char string[100];
    file_pointer_read = fopen(av[1], "r");
    
    if(file_pointer_read == NULL) {
        printf("not able open file\n");
    } else {
        while(fgets(string, 100, file_pointer_read)) {// can use stdin soo could use for input validation.
            printf("%s", string);                     // tho it keeps newline gets() removes newline. but isnt recommended to use gets().
        }
    }

    
    fclose(file_pointer_read);
    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>

int get_length(char* string){
    // int i = 0;
    // for(i = 0; string != '\0'; i++){}
    // return i;
}

int main(int arrayCount , char** fileName){
    
    if(arrayCount < 2){
        printf("throw in a file stupid!\n");
        return 0;
    }

    char* string = "testfile"; 
    char return_string[30] = "string";
    int test_int = 10 , return_int =  0;
    char character;
    
    int i = 0;
    for(i = 1; arrayCount > i; i++){
        char* grab_string = fileName[i];
        //printf("%s\n" , grab_string);
        FILE *fpointer;

        fpointer = fopen(grab_string , "r");

        if(fpointer == NULL){
            printf("you fucked up");
            exit(1);
        }
        while(1){
            character = fgetc(fpointer);
            if(feof(fpointer)){
                break;
            }
            printf("%c" , character);
    }

    fclose(fpointer);
    }

    //printf("%d\n" , i);
    //printf("%s\n" , grab_string);

    // FILE *fpointer;

    // fpointer = fopen("test.txt" , "r");

    // if(fpointer == NULL){
    //     printf("you fucked up");
    //     exit(1);
    // }

    //fprintf(fpointer , "%s\n%d" , string , test_int);//used to write to file i think
    //fscanf(fpointer , "%s%d%d" , return_string , &return_int , &return_int);
    //printf("%d %s\n" , return_int , return_string);
    //fprintf(filepointer , "%s" , string);

    // while(1){
    //     character = fgetc(fpointer);
    //     if(feof(fpointer)){
    //         break;
    //     }
    //     printf("%c" , character);
    // }

    // fclose(fpointer);

    return 0;
}
*/