#include <stdio.h>

void printHello(){
	int value = 13;
	
	printf("Hello world from execution thread %i\n", value);
}

int main(void){
	printHello();

	return 0;
	
}

