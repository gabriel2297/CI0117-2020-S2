#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BILLION 1E9

// El thread secundario simplemente ejecuta una función cuyo cuerpo es vacío.
void* emptyPthreadFunction(void* args) {
    return NULL;
}

int main(int argc, char* argv[]) {
    size_t T = 1;
    if (argc > 1) {
        T = (size_t) strtoul(argv[1], NULL, 10);
    }

    /**
     * 1. Crear un arreglo de pthreads que tenga la cantidad de pruebas que el usuario especifico
     * 2. Inicializar el reloj
     * 3. Crear un nuevo thread
     * 4. Hacer un join para esperar que ejecute el codigo
     * 5. Finalizar el reloj y guardar el resultado;
     * https://www.qnx.com/developers/docs/6.3.0SP3/neutrino/lib_ref/c/clock_gettime.html
    */
    struct timespec inicio, fin;
    double accum = 1000000;
    pthread_t *pthread_list = malloc((size_t) (T * sizeof(pthread_t)));
    for(size_t x=0;x<T; ++x){
        double tmp = 0;
        clock_gettime(CLOCK_REALTIME, &inicio);        
        pthread_create(&pthread_list[x], NULL, emptyPthreadFunction, NULL);
        pthread_join(pthread_list[x], NULL);
        clock_gettime(CLOCK_REALTIME, &fin);
        tmp = ( fin.tv_sec - inicio.tv_sec ) + ( fin.tv_nsec - inicio.tv_nsec ) / BILLION;
        printf("Valor para el thread %zu: %lf\n", x+1, tmp);
        if(tmp < accum){
            accum = tmp;
        }
    }
    printf("El mejor tiempo de creacion y destruccion de threads calculado fue de %lf, para un total de %zu pruebas\n", accum, T);
    
    // liberar memoria
    free(pthread_list);
}