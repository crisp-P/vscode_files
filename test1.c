#include <stdio.h>
#include <string.h>

int my_strlen(char *);

int main() {
   char str1[100] = "This is ", str2[] = "programiz.com";

   // concatenates str1 and str2
   // the resultant string is stored in str1.
   strcat(str1, str2);

   puts(str1);
   puts(str2);
   printf("%d\n", str1[40]);

   return 0;
}

int my_strlen(char *string) {
    int size = 0;
    if(string[0] == '\0') {
        return 0;
    }
    while(string[size] != '\0') {
        size++;
    }
    return size;
}