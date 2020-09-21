#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


/* Definición de estructuras */
typedef struct {
    size_t total;
    pthread_barrier_t barrier;
    pthread_mutex_t mutex;
} shared_data_t;

typedef struct {
    size_t thread_num;
    shared_data_t * shared_data;
} thread_data_t;


void * rendezvous_barrier(void * args){
    size_t counter = 0;
    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_data_t* shared_data = data->shared_data;

    /* Se bloquea el contador, de manera que solo un hilo puede incrementar su valor a la vez */
    pthread_mutex_lock(&shared_data->mutex);
        counter++;
    pthread_mutex_unlock(&shared_data->mutex); 
        printf("Contador aumentado, esperaré a los demás\n");
        /* Se comprueba si el valor del contador es igual a la cantidad de hilos */
        if (counter != shared_data->total){
            pthread_barrier_wait(&shared_data->barrier);
        }
        printf("Ya han llegado los demás, puedo finalizar\n");

    return NULL;
}

int main(int argc, char * arg[]){
    size_t thread_count = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    /* Definición de los arreglos */
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    /* Inicialización del mutex y la barrera */
    pthread_mutex_init(&shared_data->mutex, NULL);
    pthread_barrier_init(&shared_data->barrier, NULL, thread_count);

    /* Ciclo para creación de hilos y asignación de datos a los mismos */
    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, rendezvous_barrier, (void*)&thread_data_list[i]);
    }    

    /* Unión de los hilos */
    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    /* Destrucción y liberación de memoria */
    pthread_barrier_destroy(&shared_data->barrier);
    pthread_mutex_destroy(&shared_data->mutex);

    free(threads);
    free(shared_data);
    free(thread_data_list);

    return 0;
}