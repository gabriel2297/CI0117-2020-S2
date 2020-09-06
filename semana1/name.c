#include <stdio.h>
#define MAX_NAME_CHARS = 7;

int main() {

    printf("What is your name? ");
    char name[6];
    scanf("%6s", name);
    for(int x = 0; x < 6; x++){
        printf("Printing value at index %i: %c\n", x, name[x]);
    }
    return 0;
}