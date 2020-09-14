#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_barrier_t barrier;
pthread_mutex_t lock;

typedef struct {
    size_t total_threads;
    int position;
    int winning_thread;
} shared_data_t;

typedef struct {
    size_t thread_num;
    shared_data_t* shared_data;
} thread_data_t;

void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds)
{
	useconds_t duration = min_milliseconds;
	useconds_t range = max_milliseconds - min_milliseconds;
	if ( range > 0 )
		duration += rand() % range;
	usleep( 1000 * duration );
}

void* threadRace(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_data_t* shared_data = data->shared_data;

    random_sleep(100, 500);
    printf("Thread %zu/%zu: I am ready!\n", thread_num, shared_data->total_threads);
    // esperar por los demas threads
    pthread_barrier_wait(&barrier);
    // el thread desperto ya que el barrier nos dejo entrar, imprimir el numero
    // obtener el lock ya que necesitamos incrementar una variable compartida
    // guardar el thread que gano
    pthread_mutex_lock(&lock);
    if(shared_data->winning_thread < 0)
        shared_data->winning_thread = thread_num;
    printf("Thread %zu/%zu: I arrived at position %i.\n", thread_num, shared_data->total_threads, shared_data->position);
    ++shared_data->position;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char* arg[]) {

    size_t thread_count = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }
    
    // plantar la semilla, obtiene el tiempo del reloj de nuestra PC para generar un numero aleatorio
    srand(time(NULL));

    // pedir memoria para threads y la informacion compartida
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));
    shared_data_t* shared_data = malloc((size_t)sizeof(shared_data_t*));
    shared_data->total_threads = thread_count;
    shared_data->position = 1;
    shared_data->winning_thread = -1;

    // crear mutex y barrier
    pthread_mutex_init(&lock, NULL);
    pthread_barrier_init(&barrier, NULL, thread_count);
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    // crear los threads
    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, threadRace, (void*)&thread_data_list[i]);
    }

    // esperar a que todos los threads terminen
    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("************************\n*  WINNING THREAD: %i!  *\n************************\n", shared_data->winning_thread);
    
    // eliminar mutex y barrier
    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&barrier);

    free(threads);
    free(shared_data);
    free(thread_data_list);

    return 0;
}