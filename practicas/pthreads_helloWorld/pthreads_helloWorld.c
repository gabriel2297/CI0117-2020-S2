#include <stdio.h>
#include <pthread.h>

void *helloWorld(void *args) {
    printf("Hello world from the second thread\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    printf("Argv[0]: %s\nArgv[1]: %s\n", argv[0], argv[1]);
    printf("Total args: %i\n", argc);
    pthread_t thread;
    pthread_create(&thread, NULL, helloWorld, NULL);
    pthread_join(thread, NULL);
    printf("Hello from main thread\n");
    return 0;
}