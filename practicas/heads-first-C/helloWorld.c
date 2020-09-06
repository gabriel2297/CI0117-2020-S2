#include <stdio.h>

void changeNum(int *value){
	printf("Inside changeNum. Got value %i, located at %p. Changing it to 40\n", *value, value);
	*value = 40;
}

int main(){
	int value = 30;
	printf("My value is %i and is located at %p\n", value, &value);
	changeNum(&value);
	printf("My value has been changed to %i and is located at %p\n", value, &value);
	return 0;
}

