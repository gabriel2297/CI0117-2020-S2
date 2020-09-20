#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct {
    sem_t semaphoreA;
    sem_t semaphoreB;
} shared_data_t;

void* sayHelloA(void* arg);
void* sayHelloB(void* arg);

int main(int argc, char* argv[]) {

    if(argc != 1) {
        printf("This program does not accept more than 1 argument (program name)\n");
        return -1;
    }
    
    // crear los threads que necesitamos
    pthread_t a;
    pthread_t b;

    // crear el struct con la informacion necesaria e inicializar el semaforo
    shared_data_t* shared_data = malloc((size_t) sizeof(shared_data_t));
    sem_init(&shared_data->semaphoreA, 0, 0);
    sem_init(&shared_data->semaphoreB, 0, 0);

    pthread_create(&a, NULL, sayHelloA, (void*)shared_data);
    pthread_create(&b, NULL, sayHelloB, (void*)shared_data);

    // esperar a que los threads terminen
    pthread_join(a, NULL);
    pthread_join(b, NULL);

    // destruir el semaforo una vez termina el programa
    sem_destroy(&shared_data->semaphoreA);
    sem_destroy(&shared_data->semaphoreB);

    //liberar memoria
    free(shared_data);

    return 0;
}

void* sayHelloA(void* arg) {
    shared_data_t* shared_data = (shared_data_t*) arg;
    printf("A: Hola! Durmiendo por 10 segundos...\n");
    sleep(10);
    printf("A: desperté, notificando a B\n");
    sem_post(&shared_data->semaphoreA);
    printf("A: esperando a B...\n");
    sem_wait(&shared_data->semaphoreB);
    printf("A: Recibí señal de B, terminando\n");
    return NULL;
}

void* sayHelloB(void* arg) {
    shared_data_t* shared_data = (shared_data_t*) arg;
    sleep(3);
    printf("\t\t\t\t\tB: Hola!. Esperando a que A nos notifique si podemos seguir...\n");
    sem_wait(&shared_data->semaphoreA);
    printf("\t\t\t\t\tB: Recibí notificación de A! Le diré a A que puede continuar en ");
    fflush(stdout);
    for(int x=10;x>=1;x--){
        printf("%i.. ", x);
        fflush(stdout);
        sleep(1);
    }
    printf("B terminó\n");
    sem_post(&shared_data->semaphoreB);
    return NULL;
}