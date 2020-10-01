#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

typedef struct timespec walltime_t;

typedef struct {
    double a;
    double b;
    double n;
    double delta;
    double total_area;
    pthread_mutex_t mutex;
} shared_data_t;

typedef struct 
{
    /* Cada hilo tiene un limite inferior y superior que corresponde al intervalo donde se ubican los rectángulos */
    double lower_limit;
    double upper_limit;
    shared_data_t * shared_data;
} thread_data_t;


void walltime_start(walltime_t* start){
    clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;

    return elapsed;
}    

/* @brief definicion de la funcion f(x) a la cual se le calculara la suma de riemann
    @param valor de x evaluado
    @return resultado de la funcion al evaluar x*/
double function(double x){
    return x*x + 1;
}

/* @brief Calcular el area de la suma de riemann con n rectángulos por m hilos en el area delimitada por a y b
    @param args puntero a argumentos de tipo void
    @return vacio */
void * riemman_sum(void * args){
    thread_data_t* data = (thread_data_t*) args;
    shared_data_t* shared_data = data->shared_data; 

    double partial_area = 0.0;
    
    /* Calculo por parte de los hilos de las areas correspondientes
        Dado que cada hilo se encarga que calcular el area de un número determinado de rectángulos, es necesario ajustar los limites inferiores
        y superiores del area a calcular, mientras que esta sea menor que b. Posteriormente el iterador avanza a su posicion actual + delta
        para desplazarse por el area. */
    for (double i = data->lower_limit; i < data->upper_limit && i < (shared_data->b); i = i + shared_data->delta){
        /* Para evitar busy waiting se bloquea el acceso a los recursos con un mutex */
        pthread_mutex_lock(&shared_data->mutex);
            partial_area += function(i) * shared_data->delta;
        pthread_mutex_unlock(&shared_data->mutex);            
    }
        pthread_mutex_lock(&shared_data->mutex);
            shared_data->total_area += partial_area;  
        pthread_mutex_unlock(&shared_data->mutex);    

    return NULL;
}    


int main(int argc, char * argv[]){
    walltime_t* walltime = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_start(walltime);
    double a = 0.0;
    double b = 0.0;
    double n = 0.0;
    size_t thread_count = 0;

    /* Validacion de argumentos del main */
    if (argc >= 3){
        if (argv[3] > 0){
            a = (double)strtoul(argv[1], NULL, 10);
            b = (double)strtoul(argv[2], NULL, 10);
            n = (double)strtoul(argv[3], NULL, 10);
            thread_count = (size_t)strtoul(argv[4], NULL, 10);
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
    double delta = (b - a) / n;
    /* Asignacion de cantidad de rectángulos por hilos */
    size_t rects_per_thread = ceil(n / ((double) thread_count));

    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));    
    
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));

    /* Variables "globales" de los hilos */
    shared_data->delta = delta;
    shared_data->a = a;
    shared_data->b = b;

    pthread_mutex_init(&shared_data->mutex, NULL);

    for (size_t i = 0; i < thread_count; ++i){
        thread_data_list[i].shared_data = shared_data;
        thread_data_list[i].lower_limit = a;
        thread_data_list[i].upper_limit = a + rects_per_thread * delta;
        pthread_create(&threads[i], NULL, riemman_sum, (void*)&thread_data_list[i]);
        a += rects_per_thread * delta;
    }

    for (size_t i = 0; i < thread_count; ++i){
        pthread_join(threads[i],NULL);
    }
    double execution_time = walltime_elapsed(walltime);
    printf("The estimated area is: %f\n", shared_data->total_area);
    printf("The time expended was: %f\n", execution_time);

    pthread_mutex_destroy(&shared_data->mutex);
    /* Salida de los resultados */
    free(threads);
    free(shared_data);
    free(thread_data_list);
    return 0;
}

