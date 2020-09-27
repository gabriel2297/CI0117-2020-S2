#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


/* @brief definicion de la funcion f(x) a la cual se le calculara la suma de riemann
    @param valor de x evaluado
    @return resultado de la funcion al evaluar x*/
double function(double x){
    return x*x + 1;
}

/* @brief calcular el resultado de la suma de riemman en los puntos determinados 
    @param a primer punto del invervalo a evaluar, b segundo punto del intervalo a evaluar, n cantidad de rectangulos a crear
    @return resultado de la suma de riemann  */
double riemman_sum(double a, double b, double n){
    double delta = (b - a) / n;
        if (delta < 0){
            delta = -1 * delta;
        }

    double result = 0.0;

    for (size_t i = 0; i < n; ++i){
        result += function(a) * delta;
        a += delta;
    }
    return result;
}    

int main(int argc, char * argv[]){
    double a = 0.0;
    double b = 0.0;
    double n = 0.0;
    double execution_time = 0.0;

    /* Validacion de argumentos del main */
    if (argc >= 3){
        if (argv[3] > 0){
            a = (double)strtoul(argv[1], NULL, 10);
            b = (double)strtoul(argv[2], NULL, 10);
            n = (double)strtoul(argv[3], NULL, 10);
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
    /* Inicializacion del conte del reloj */
    clock_t begin = clock();
    double result = riemman_sum(a, b, n);
    clock_t end = clock();

    /* Salida de los resultados */
    printf("The approximation of the area is %f \n", result);
    execution_time += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("the time taken to perform the calculations was %f\n", execution_time);

    return 0;
}
