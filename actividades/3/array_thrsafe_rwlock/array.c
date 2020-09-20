#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include "array.h"


typedef struct array
{
	void** elements;
	size_t capacity;
	size_t count;
	pthread_rwlock_t rwlock; // declarando el lock para lectura/escritura, uno por array
} array_t;

array_t* array_create(size_t capacity)
{
	assert(capacity);

	array_t* array = calloc(1, sizeof(array_t));
	if ( array == NULL )
		return NULL;

	array->capacity = capacity;
	array->count = 0;

	array->elements = (void**)malloc( capacity * sizeof(void*) );
	if ( array->elements == NULL )
		return free(array), NULL;

	pthread_rwlock_init(&array->rwlock, NULL); // array creado exitosamente, inicializar los locks
	return array;
}

void array_destroy(array_t* array)
{
	assert(array);

	pthread_rwlock_destroy(&array->rwlock); // array creado exitosamente, inicializar los locks
	free(array->elements);
	free(array);
}

int array_increase_capacity(array_t* array)
{
	assert(array);

	size_t new_capacity = 10 * array->capacity;
	void** new_elements = (void**)realloc( array->elements, new_capacity 
			* sizeof(void*) );
	if ( new_elements == NULL )
		return -1;

	array->capacity = new_capacity;
	array->elements = new_elements;

	return 0; // Success
}

int array_decrease_capacity(array_t* array)
{
	assert(array);

	size_t new_capacity = array->capacity / 10;
	if ( new_capacity < 10 )
		return 0;

	void** new_elements = (void**)realloc( array->elements, new_capacity * sizeof(void*) );
	if ( new_elements == NULL )
		return -1;

	array->capacity = new_capacity;
	array->elements = new_elements;

	return 0; // Success
}

size_t array_get_count(array_t* array)
{
	assert(array);
	pthread_rwlock_rdlock(&array->rwlock); // lectura es compartida, bloquear para leer
		size_t localCount = 0;
		localCount = array->count;
	pthread_rwlock_unlock(&array->rwlock);
	return localCount;
}

void* array_get_element(array_t* array, size_t index)
{
	assert(array);
	assert( index < array_get_count(array) );
	pthread_rwlock_rdlock(&array->rwlock); // no se usa por ningun lado pero podria utilizarse, bloquear para lectura
		void* elementAtIndex = 0;
		elementAtIndex = array->elements[index];
	pthread_rwlock_unlock(&array->rwlock); // desbloquear despues de leer
	return elementAtIndex;
}

int array_append(array_t* array, void* element)
{
	assert(array);
	// bloquear para escritura
	pthread_rwlock_wrlock(&array->rwlock);
	if ( array->count == array->capacity ) {
		if ( array_increase_capacity(array) ){
			pthread_rwlock_unlock(&array->rwlock); // algo salio mal, quitar el lock antes de salir
			return -1;
		}
	}	
	assert( array->count < array->capacity );
	array->elements[array->count++] = element;
	pthread_rwlock_unlock(&array->rwlock); // todo salio bien, desbloquear
	return 0;
}

size_t array_find_first(array_t* array, const void* element, size_t start_pos)
{
	assert( array );
	pthread_rwlock_rdlock(&array->rwlock); // bloquear para lectura 
		int found = 0;
		size_t localElement = 0;
		for ( size_t index = start_pos; index < array->count; ++index ){
			if ( array->elements[index] == element ){
				found = 1;
				localElement = index;
				break;
			}
		}
	pthread_rwlock_unlock(&array->rwlock); // todo salio bien, desbloquear
	return found ? localElement : array_not_found;
}

int array_remove_first(array_t* array, const void* element, size_t start_pos)
{
	assert( array );
	size_t index = array_find_first(array, element, start_pos); // no bloquear ya que find_first bloquea para lectura
	if ( index == array_not_found ) {
		return -1;
	}
	pthread_rwlock_rdlock(&array->rwlock); // array_find_first encontro el index, bloquear para realizar cambios
	for ( --array->count; index < array->count; ++index )
		array->elements[index] = array->elements[index + 1];
	if ( array->count == array->capacity / 10 )
		array_decrease_capacity(array);
	pthread_rwlock_unlock(&array->rwlock); // todo bien, desbloquear
	return 0; // Removed
}
