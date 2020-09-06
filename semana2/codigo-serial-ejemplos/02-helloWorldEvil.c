#include <stdio.h>

int value = 13; //global variables are EVIL

int main(void){
	printf("Hello world from execution thread %i\n", value);

	return 0;
	
}
