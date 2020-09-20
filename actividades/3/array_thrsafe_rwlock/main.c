#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"

void print_array(const char* name, array_t* array);
void test_arrays(array_t* array1, array_t* array2);
void* test_array(void* data);

int main()
{
    array_t* array1 = array_create(100);
    array_t* array2 = array_create(100);

	test_arrays(array1, array2);

	print_array("array1", array1);
	print_array("array2", array2);

	array_destroy(array1);
	array_destroy(array2);

	return 0;
}

void print_array(const char* name, array_t* array)
{
	printf("%s: %zu elements\n", name, array_get_count(array));
	fflush(stdout);
}

void test_arrays(array_t* array1, array_t* array2)
{
	srand( (unsigned)((unsigned)time(NULL) + (unsigned)clock()) );

	size_t thread_count = 10 + rand() % 20;
	pthread_t* threads = (pthread_t*) malloc( thread_count * sizeof(pthread_t) );

	for ( size_t current = 0; current < thread_count; ++current )
		pthread_create( threads + current, NULL, test_array, current % 2 ? array2 : array1 );

	for ( size_t current = 0; current < thread_count; ++current )
		pthread_join( threads[current], NULL );

	free(threads);
}

void* test_array(void* data)
{
    array_t* array = (array_t*)data;

	for ( size_t index = 0, count = 1000 + rand() % 10000; index < count; ++index )
	{
		size_t num = rand() % 100;
		if ( num >= 10 )
			array_append( array, (void*)(num) );
		else
		{
			num += rand() % 90;
			if ( array_find_first(array, (void*)num, 0) != array_not_found )
				array_remove_first(array, (void*)num, 0);
		}
	}

	return NULL;
}