#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_putchar(char);
void square_length(int);
void square_height(int, int);
// | == 179 o == 111 - == 45
int main(int ac, char **av) {
    
    int length = atoi(av[1]);
    int height = atoi(av[2]);
    //char building_blocks[3] = "o|-";
    for(int i = 1; i <= height; i++) {
        if(i == 1 || i == height) {
            square_length(length);
        } else {
            square_height(length, height);
        }
    }
    return 0;
}

void my_putchar(char c) {
    write(1 , &c , 1);
}

void square_length(int length) {
    for(int i = 1; i <= length; i++) {
        if(i == 1 || i == length) {
            my_putchar('o');
        } else {
            my_putchar('-');
        }
        if(i == length) {
            my_putchar('\n');
        }
    }
    
}
void square_height(int length, int height) {
    for(int i = 1; i <= length; i++) {
        if(i == 1 || i == length) {
            my_putchar('|');
        } else if(i > 1) {
            my_putchar(' ');
        }
        if(i == length) {
            my_putchar('\n');
        } 
    }
}