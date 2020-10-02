#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "pthread_barriers.h"


pthread_mutex_t mutex;
pthread_barrier_t barrier;

/* Definicion de una estructura para mantener los datos compartidos entre hilos */
typedef struct {
    double a;
    double b;
    double result;
} pthread_shared_data;

/* Definicion de una estructura para mantener los datos propios de cada hilo */
typedef struct {
    double result;
    long rectangulos;
    double delta;
    int thread_num;
    pthread_shared_data* shared_data;
} pthread_local_data;

/*  @brief definicion de la funcion f(x) a la cual se le calculara la suma de riemann
    @param valor de x evaluado
    @return resultado de la funcion al evaluar x*/
double function(double x){
    return x*x + 1;
}

/*  @brief calcular el resultado de la suma de riemman en los puntos determinados
    @param a primer punto del invervalo a evaluar, b segundo punto del intervalo a evaluar, n cantidad de rectangulos a crear
    @return resultado de la suma de riemann  */
void* riemman_sum(void* data){
    pthread_local_data pthread_data = *(pthread_local_data*)data;
    pthread_shared_data* shared_data = pthread_data.shared_data;
    
    double delta = pthread_data.delta;
    // esperar a los demas hilos para empezar, ya que no queremos cambiar a hasta ese momento
    pthread_barrier_wait(&barrier);
    pthread_mutex_lock(&mutex);
    for (size_t i = 0; i < pthread_data.rectangulos; ++i){
            pthread_data.result += function(shared_data->a) * delta;
            shared_data->a += delta;
    }

    // una vez finalizado sumar los calculos de este hilo al resultado total
    shared_data->result += pthread_data.result;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char * argv[]){
    pthread_shared_data* shared_data;
    long totalThreads, n = 0.0;
    double execution_time = 0.0;

    /* Validacion de argumentos del main */
    if (argc >= 4){
        if (argv[3] > argv[4]) {
            // si el numero de rectangulos es menor a la cantidad de hilos, tirar error
            printf("Error, thread num can't be less than rectangles\n");
            return 1;
        }
        if (argv[4] > 0){
            n = (long)strtoul(argv[3], NULL, 10);
			totalThreads = (long)strtoul(argv[4], NULL, 10);
            shared_data = malloc((size_t) sizeof(shared_data));
            shared_data->a = (double)strtoul(argv[1], NULL, 10);
            shared_data->b = (double)strtoul(argv[2], NULL, 10);
            shared_data->result = 0.0;
        }
        else {
            printf("Error invalid format of parameters, n cannot be equals to zero\n");
            return 1;
        }
    }
    else {
        printf("Error, invalid number of parameters\n");
        return 1;
    }

    /* Inicializar hilos y datos compartidos */
    pthread_t* threads =  malloc((size_t) (totalThreads * sizeof(pthread_t)) );
    pthread_local_data* local_data = malloc((size_t) (totalThreads * sizeof(pthread_local_data)));
    
    /* Inicializar el mutex y el barrier*/
    pthread_mutex_init(&mutex, NULL);
    
    /* Empezar a contar */
    clock_t begin = clock();

    /* Calcular cuantos rectangulos le toca a cada hilo */
    long num_rectangulos_por_hilo;
    long restante_modulo;
    int impar = 0;
    /*  Explicacion: 
        - si es divisible entre 0 significa que cada hilo va a tener la misma cantidad
        - si no, entonces un hilo va a tener lo que le falta a la sumatoria de todos los otros hilos
        Ejemplos: 
        1.  n = 375
            totalThreads = 23
            375%23 = 7, eso es igual a 0? no, pasamos al else
            n / (totalThreads - 1)
                375/22 = 17 (division de enteros), entonces 22 hilos van a tener 17 rectangulos
            n - (num_rectangulos_por_hilo*(totalThreads - 1))
                375 - (17 * (23-1))
                375 - (17 * 22)
                375 - 374
                    1   un hilo va a tener solo un rectangulo
        2.  n = 226
            totalThreads = 37
            226%37 = 4, eso es igual a 0? no, pasamos al else
            n / (totalThreads - 1)
                226/36 = 6 (division de enteros), entonces 36 hilos van a tener 6 rectangulos
            n - (num_rectangulos_por_hilo*(totalThreads - 1))
                226 - (6 * (37-1))
                226 - (6 * 36)
                226 - 216
                    10  un hilo va a tener 10 rectangulos
        3.  n = 220
            totalThreads = 10
            220%10 = 0, eso es igual a 0? Si, pasamos al if
            220/10 = 22, entonces todos los 10 hilos tendran 22 rectangulos            
    */
    while(totalThreads > n) {
        totalThreads /= 2;
    }
    if (fmod(n,totalThreads) == 0.0) {
        num_rectangulos_por_hilo = n / totalThreads;
    }
    else {
        impar = 1;
        num_rectangulos_por_hilo = n / (totalThreads - 1);
        restante_modulo = n - (num_rectangulos_por_hilo*(totalThreads - 1));
    }

    // printf("Creando hilos.\n\t- total de hilos a usar: %ld\n\t- num_rectangulos_por_hilo: %ld\n\t- restante_modulo: %ld\n", totalThreads, num_rectangulos_por_hilo, restante_modulo);
    double delta = (shared_data->b - shared_data->a) / n;
        if (delta < 0){
            delta = -1 * delta;
        }

    pthread_barrier_init(&barrier, NULL, totalThreads);
    /* Inicializar cada hilo y pasarle sus datos */
    for(size_t x = 0; x < totalThreads; x++) {
        if (x+1 == totalThreads && impar){
            local_data[x].delta = delta;
            local_data[x].thread_num = x;
            local_data[x].rectangulos = restante_modulo;
            local_data[x].result = 0.0;
            local_data[x].shared_data = shared_data;
        }
        else {
            local_data[x].delta = delta;
            local_data[x].thread_num = x;
            local_data[x].rectangulos = num_rectangulos_por_hilo;
            local_data[x].result = 0.0;
            local_data[x].shared_data = shared_data;
        }
        // printf("Hilo %li creado con los siguientes datos: \n", x);
        // printf("\t- rectangulos: %ld\n\t- delta: %f\n\t- resultado: %f\n", local_data[x].rectangulos, local_data[x].delta, local_data[x].result);
        // printf("\t- shared data:\n\t- a: %f\n\t- b: %f\n\t- resultado: %f\n", local_data[x].shared_data->a, local_data[x].shared_data->b, local_data[x].shared_data->result);
        pthread_create(&threads[x], NULL, riemman_sum, (void*)&local_data[x]);
    }

    /* Esperar a los hilos y dejar de contar*/
    for (int i = 0; i < totalThreads; ++i) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();

    /* Salida de los resultados */
    printf("The approximation of the area is %f \n", shared_data->result);
    execution_time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("the time taken to perform the calculations was %f\n", execution_time);

    /* Liberar la memoria */
    free(threads);
    free(shared_data);
    free(local_data);
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    return 0;
}
