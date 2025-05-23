#include <stdio.h>

void passing_int(int* num) {

    //num = 1;
    *num = *num + 1;
    *num = *num + 1;

}
int main() {
    
    int num = 0;
    passing_int(&num);
    printf("hello %d\n", num);
    return 0;
}