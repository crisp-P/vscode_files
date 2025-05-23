#include<stdio.h>

int my_strlen(const char *string) {
    int size = 0;
    if(string == NULL) {
        return 0;
    }
    while(string[size] != '\0') {
        size++;
    }
    return size;
}


int main(int ac, char **av) {   
    
    int how_many_filled = 0;
    //if(av[j][k] != ""){}
    for(int i = 0; i < 255; i++) {
        for(int j = 1; j < ac; j++) {
            for(int k = 0; av[j][k] != '\0'; k++) {
                if(i == av[j][k]) {
                    how_many_filled++;
                }
            }
        }
        if(how_many_filled > 0) {
            printf("%c:%d\n", i, how_many_filled);
            how_many_filled = 0;
        }   
    }
    
    return 0;
}

//soo what i need to do is grab character from av and save it some were or count it some how.
//one way to do it is save everything into a array and sort it.
//another way is to make 2d array and do samething but its already sorted.

/*
#include<stdio.h>

int my_strlen(const char *string) {
    int size = 0;
    if(string == NULL) {
        return 0;
    }
    while(string[size] != '\0') {
        size++;
    }
    return size;
}

void filling_array(char c, int* how_many_filled, char count[100][100]){
    int j = 0;
    for(int i = 0; i <= *how_many_filled; i++){
        //printf("in first for loop i = %d c = %c\n" , i , c);
        if(c == count[i][0]) {
            //printf("in if c = %d, count[i][0] = %d\n", c ,count[i][0]);
            for(j = 0; count[i][j] != '\0'; j++) {
            //    printf("in second for loop\n");
            }

            count[i][j] = c;
            count[i][j+1] = '\0';
            break;
            
        }else if(c != count[i][0] && *how_many_filled == i) {
            count[i][0] = c;
            count[i][1] = '\0';
            *how_many_filled = *how_many_filled + 1;
            //printf("in else if filled slots = %d count = %s\n", *how_many_filled , count[i]);
            break;
        }
    }
}
int main(int ac, char **av) {   
    
    
    
    int how_many_filled = 0;
    int sort = 0;
    char count[100][100];

    for(int i = 1; i < ac; i++) {
        for(int j = 0; av[i][j] != '\0'; j++) {
            filling_array(av[i][j], &how_many_filled, count);
        }
    }

    for(int i = 0; i < 255; i++) {
        for(int j = 0; j < how_many_filled; j++) {
            //printf("%d, %d\n" , i , count[i][0]);
            if(i == count[j][0]) {
                //printf("hi");
                printf("%c: %d\n" , count[j][0], my_strlen(count[j]));
            }
        }
        
    }
    
    return 0;
}
*/