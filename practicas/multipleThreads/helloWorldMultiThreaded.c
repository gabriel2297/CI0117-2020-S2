#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    size_t thread_num;
} thread_info_t;

void* helloWorldThread(void* args) {
    thread_info_t *thread_info = (thread_info_t*) args;
    size_t thread_num = thread_info->thread_num;
    printf("Hello world from thread %zu\n", thread_num);
    return NULL;
}

int main(int argc, char* argv[]) {
    size_t total_threads; 

    // if the user didn't specify threads, say hello from the main thread
    if(argc == 1) {
        printf("User did not put any threads. Using main thread only\n");
        total_threads = 0;
    }
    // else, say hello from the total size of threads 
    else {
        total_threads = (size_t) strtoul(argv[1], NULL, 10);
        printf("User specified %zu threads, proceeding.\n", total_threads);
        pthread_t* threads = malloc((size_t)(total_threads * sizeof(pthread_t)));
        thread_info_t* thread_info_list = malloc((size_t)(total_threads * sizeof(thread_info_t)));

        for(size_t x=0; x<total_threads; ++x) {
            thread_info_list[x].thread_num = x;
            pthread_create(&threads[x], NULL, helloWorldThread, (void*)&thread_info_list[x]);
        }

        free(threads);
        free(thread_info_list);
    }

    printf("Hello world from main thread");


    return 0;
}