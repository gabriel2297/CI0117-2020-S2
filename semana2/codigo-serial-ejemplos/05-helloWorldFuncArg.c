#include <stdio.h>

void printHello(int value){
	printf("Hello world from execution thread %i\n", value);
}

int main(void){
	int value = 13;

	printHello();

	return 0;
	
}

