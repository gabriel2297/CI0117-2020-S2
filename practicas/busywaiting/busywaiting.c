/*
 * busywaiting.c
 * 
 * Simple C program demonstrating shared memory between threads, busy waiting, uses heap (malloc) and stack (per thread).
 * Takes 2 arguments, the total threads first and the chosen thread second. There is no data race because we only have 
 * 1 single thread writing, all others read.
 * Why is it useless? Because each thread will have to wait until the chosen thread is hit, at that point the threads will continue
 * execution.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    size_t message;
    size_t chosen_thread;
    size_t next_thread;
} shared_message_t;

typedef struct {
    size_t thread_num;
    shared_message_t *shared_message;
} thread_info_t;

void* helloWorldThread(void* args) {
    // get the thread_info pointer from the arguments
    thread_info_t *thread_info = (thread_info_t*) args;
    // while the thread number is different than the one to be executed, wait for the others to be executed. 
    while(thread_info->thread_num != thread_info->shared_message->next_thread);
    if(thread_info->thread_num == thread_info->shared_message->chosen_thread) {
        printf("Hello from thread %zu, the chosen thread. The message is %zu and I'm changing it to 2021\n", thread_info->thread_num, thread_info->shared_message->message);
        thread_info->shared_message->message = 2021;
        ++thread_info->shared_message->next_thread;
        return NULL;
    }
    printf("Hello from thread %zu, the message is %zu\n", thread_info->thread_num, thread_info->shared_message->message);
    ++thread_info->shared_message->next_thread;
    return NULL;
}

int main(int argc, char* argv[]){
    
    size_t total_threads;
    size_t chosen_thread;

    /**
     * Check a few things, such as if the user specified the threads required 
     * Also check if the chosen thread is not bigger than the total amount of threads or less than 0
     **/
    if(argc >= 3) {
        total_threads = (size_t) strtoul(argv[1], NULL, 10);
        chosen_thread = (size_t) strtoul(argv[2], NULL, 10);
        if(chosen_thread < 0 || chosen_thread > total_threads) {
            printf("Chosen thread (%zu) can't be more than the total threads (%zu)\n", chosen_thread, total_threads);
            return 1;    
        }
    }
    else {
        printf("Invalid amount of params, needs at least 2\n");
        return 1;
    }

    // start by initializing the shared message
    shared_message_t *shared_message = malloc((size_t) sizeof(shared_message_t));
    shared_message->chosen_thread = chosen_thread;
    shared_message->message = 2020;
    shared_message->next_thread = 0;

    // create a pthread array of pointers
    pthread_t *threads = malloc((size_t) (total_threads * sizeof(pthread_t)));

    // create a thread_info_t array to hold the info of each thread in memory
    thread_info_t *thread_info_list = malloc((size_t) (total_threads * sizeof(thread_info_t)));
    
    // start initializing the threads, each with their respective thread_info_t
    for(size_t x=0; x<total_threads;++x){
        thread_info_list[x].shared_message = shared_message;
        thread_info_list[x].thread_num = x;
        pthread_create(&threads[x], NULL, helloWorldThread, (void*)(&thread_info_list[x]));
    }

    // wait for all the threads to be done
    for(size_t x=0;x<total_threads;++x){
        pthread_join(threads[x], NULL);
    }

    printf("Child threads are done, main thread exiting...\n");
    // remember to free up the memory taken
    free(shared_message);
    free(threads);
    free(thread_info_list);

    return 0;
}