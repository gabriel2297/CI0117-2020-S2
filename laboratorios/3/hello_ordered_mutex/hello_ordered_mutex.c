#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// declaring mutex 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condition_t = PTHREAD_COND_INITIALIZER;

typedef struct {
    int next_thread;
} shared_data_t;

typedef struct {
    int thread_num;
    shared_data_t* shared_data;
} thread_data_t;

void* helloWorld(void* args) {
    thread_data_t *thread_data = (thread_data_t*) args;
    int thread_num = thread_data->thread_num;
    shared_data_t* shared_data = thread_data->shared_data;
    //printf("Thread %i created successfully, trying to acquire the lock\n", thread_num);
    pthread_mutex_lock(&lock);
    //printf("Thread %i got the lock\n", thread_num);
    while(thread_num != shared_data->next_thread) {
        //printf("Next thread is %i, I am %i... sleeping\n", shared_data->next_thread, thread_num);
        pthread_cond_wait(&condition_t, &lock);
    }
    ++shared_data->next_thread;
    printf("Hello from thread %i, next thread is %i\n", thread_num, shared_data->next_thread);
    pthread_cond_broadcast(&condition_t);
    pthread_mutex_unlock(&lock);
    //printf("Thread %i exiting after unlock\n", thread_num);
    pthread_exit(NULL);
}


int main(int argc, char* arg[]) {

    int thread_count = 0;

    if (argc >= 2) {
        thread_count = (int)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    // crear la shared data y las condiciones
    shared_data_t* shared_data = (shared_data_t*)malloc(sizeof(shared_data_t));

    // inicializar el lock y la condicion
    pthread_mutex_init(&lock, NULL);

    // pedir memoria en heap y hacer spawn de varios threads con su respectiva informacion (thread_data_t)
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    //  crear cada thread con su numero de thread
    for (int i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        //printf("Created thread %i\n", i);
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
    }

    for (int i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    free(shared_data);
    free(threads);
    free(thread_data_list);

    return 0;
}