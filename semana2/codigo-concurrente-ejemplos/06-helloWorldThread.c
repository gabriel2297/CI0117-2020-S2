#include <pthread.h>
#include <stdio.h>

/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
    void *(*start_routine)(void*), void *arg);
*/

void* run(void* data){
	//(void)data;
	size_t thread_num = (size_t)data;
	printf("Hello world from secondary thread %zu\n", thread_num);
	return NULL;
}

int main(void){
	pthread_t thread;
	pthread_create(&thread, NULL, run, (void*)13);
	printf("Hello world from main thread\n");
	pthread_join(thread, NULL);

	return 0;
}

