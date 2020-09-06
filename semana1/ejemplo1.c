#include <stdio.h>

int printerFunction(int *number){
    printf("Number: %i\n", *number);
    *number++;
    return 0;
}

int main() {
    printf("Count up to: ");
    int num;
    scanf("%i", &num);
    for(int counter = 1; counter <= num; counter++) {
        printerFunction(&counter);
    }   
    return 0;
}