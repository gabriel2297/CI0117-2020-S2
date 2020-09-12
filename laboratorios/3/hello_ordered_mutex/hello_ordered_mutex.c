#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex_t = PTHREAD_MUTEX_INITIALIZER;

int next_thread = 0;
pthread_cond_t* condition_t;
// typedef struct {
//     int next_thread;
//     pthread_cond_t* condition_t;
// } shared_data_t;

typedef struct {
    int thread_num;
    // shared_data_t* shared_data;
} thread_data_t;

void* helloWorld(void* args) {
    // obtener los datos
    thread_data_t* thread_data = (thread_data_t*) args;
    //printf("threadnum requesting lock: %i\n", thread_data->thread_num);

    // obtener el lock, si el thread aun no es el que tiene que imprimir, ponerlo a dormir
    pthread_mutex_lock(&mutex_t);
    int thread_num = thread_data->thread_num;
    //printf("threadnum with lock: %i\n", thread_data->thread_num);
    if(next_thread != thread_num) {
        //printf("threadnum accessing wait %i... putting all threads to sleep except %i\n", thread_data->thread_num, thread_data->thread_num);
        pthread_cond_wait(&condition_t[thread_num], &mutex_t);
    }
    // una vez que sale de dormir, ya puede imprimir
    next_thread++;
    printf("Hello from thread %i... next thread is %i\n", thread_num, next_thread);
    // despertar al siguiente thread para que corra
    //printf("Waking up %i\n", *next_thread);
    pthread_cond_signal(&condition_t[next_thread]);
    //printf("before, next thread is %i and current thread is %i\n", *next_thread, thread_num);
    pthread_mutex_unlock(&mutex_t);
    //printf("thread %i has unlocked the mutex\n", thread_num);
    return NULL;
}

int main(int argc, char* argv[]) {

    int thread_count = 0;

    if (argc >= 2) {
        thread_count = (int)strtoul(argv[1], NULL, 10) - 1;
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }

    // poner los datos iniciales en la informacion que vamos a compartir entre threads
    // shared_data_t* shared_data = (shared_data_t*)malloc(sizeof(shared_data_t));
    condition_t = (pthread_cond_t*) malloc((thread_count * sizeof(pthread_cond_t)));

    // crear arreglo de threads y de cada uno de los datos de ese thread
    pthread_t* threads = (pthread_t*) malloc((thread_count * sizeof(pthread_t)));
    thread_data_t* thread_info_list = (thread_data_t*) malloc((thread_count * sizeof(thread_info_list)));

    // inicializar threads y condiciones
    for(int i=0; i<thread_count; ++i) {
        thread_info_list[i].thread_num = i;
        // thread_info_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_info_list[i]);
    }

    // esperar a que los threads terminen
    for(int i=0; i<thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    // liberar la memoria
    // free(shared_data);
    free(threads);
    free(thread_info_list);

    return 0;
}