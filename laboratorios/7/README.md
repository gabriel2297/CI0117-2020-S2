# CI0117 - Laboratorio 7

## Estudiantes:
- Emmanuel Zúñiga Chaves (B98729)
- Gabriel Umaña Frías (C09913)

## Ejercicio 1 [count_primes_serial]

Calcule el tiempo que se tarda en correr el programa para un número grande de n, por ejemplo 100 millones (o similar, dependiendo de lo que permita el hardware).

```
gumanafrias@ubuntu:~/Documents/CI0117-2020-S2/laboratorios/7/count_primes_serial$ ./count_primes_serial 100000000
There are 5761455 prime numbers between 2 and 100000000
The time taken was: 162.218106s
```

## Ejercicio 2 [count_primes_parallel]

Modifique el programa del ejercicio anterior para que la solución se realice de forma paralela utilizando *parallel for* de OpenMP. Utilice *reduction* en lugar de declarar zonas críticas y especifique el *scope* de las variables. Puede utilizar la cantidad de hilos por defecto (o sea, no es necesario especificar el número de hilos con *num_threads*).

Anote el incremento de velocidad obtenido con respecto al programa del ejercicio anterior.

```
gumanafrias@ubuntu:~/Documents/CI0117-2020-S2/laboratorios/7/count_primes_parallel$ ./count_primes_parallel 100000000
There are 5761455 prime numbers between 2 and 100000000
The time taken was: 161.741188s
```
- En este caso vemos mejor rendimiento en el programa que usa hilos. Al realizarlo serial, el programa toma 162 segundos en terminar de determinar la cantidad de numeros primos de 2 a 100000000, mientras que el programa paralelo lo realiza en 161 segundos, es decir, 1 segundo mas rapido.

## Ejercicio 3 [count_primes_cyclic]

Modifique el código del programa del ejercicio 2 para que las iteraciones se distribuyan entre los hilos utilizando scheduling en tiempo de ejecución (runtime). De forma que desde la línea de comandos, antes de ejecutar el programa se modifique la variable de ambiente OMP_SCHEDULE con el valor de diferentes tipos de scheduling. Por ejemplo:

```
export OMP_SCHEDULE="static,1"
perf stat ./count_primes_cyclic 100000000
```

Realice pruebas y anote la duración utilizando las siguientes planificaciones:

```
static,1
static,N
dynamic,1
dynamic,N
```
En este caso para escoger los valores de N se obtuvo la cantidad por defecto de hilos que el hardware permitia para la ejecución del programa. Siendo N = 4, a partir de dicho valor se realizan las pruebas con las planificaciones. A continuación se presentan las tablas que resumen los resultados obtenidos:

Para valores constantes como static, 1 y dynamic, 1 se obtuvieron los siguientes resultados:
|Planificación |   Tiempo    |
|--------------|-------------|
| static, 1    | 139.890527s |
| dynamic, 1   | 97.774604s  |

Para los valores de N

|Planificación                         | static, N  | dynamic, N   |
|--------------------------------------|------------|--------------|
| N = cantidad de hilos                | 98.891831s | 97.307262s   |
| N = mitad del total de hilos         | 99.007316s | 99.290917s   |
| N = mitad del total de iteraciones   | 180.103404s| 185.410482s  |

Nóte que los resultados de las planificaciones que involucran valores de N como cantidad de hilos y mitad del total de hilos tardaron tiempos similares ubicandose entre los 97 y 99 segundos. Sin embargo, al incrementar N hacia el mitad del total de las iteraciones los tiempos se duplican.

## Guided Scheduling

En este tipo de planificacion cada hilo ejecuta un chunk de iteraciones considerablemente grande de manera que cada vez se solicita un nuevo chunk de menor tamaño para balancear las iteraciones, dicho procedimiento se realiza hasta que ya no hayan chunks disponibles. Se define el tamaño del chunk como contador del ciclo/total de hilos.

A continuación se presenta un ejemplo obtenido del sitio web: https://www.rookiehpc.com/openmp/docs/guided.php
```
int main(int argc, char* argv[])
{
    // Use 2 threads when creating OpenMP parallel regions
    omp_set_num_threads(2);
 
    // Parallelise the for loop using the dynamic schedule
    #pragma omp parallel for schedule(guided)
    for(int i = 0; i < 10; i++)
    {
        printf("Thread %d processes iteration %d.\n", omp_get_thread_num(), i);
    }
 
    return EXIT_SUCCESS;
}
```
Para la ejecución con un runtime scheduling se debe de especificar mediante la siguiente variable de ambiente:

```
export OMP_SCHEDULE="GUIDED,1"
```

A continuación se presenta la tabla actualizada con los resultados del guided scheduling:
Para valores contantes:

|Planificación |   Tiempo    |
|--------------|-------------|
| static, 1    | 139.890527s |
| dynamic, 1   | 97.774604s  |
| guided, 1    |             |

Para los diferentes valores de N:

|Planificación                         | static, N  | dynamic, N   | guided, N   |
|--------------------------------------|------------|--------------|-------------|
| N = cantidad de hilos                | 98.891831s | 97.307262s   | 96.239571s  |
| N = mitad del total de hilos         | 99.007316s | 99.290917s   | 87.831828s  |
| N = mitad del total de iteraciones   | 180.103404s| 185.410482s  | 182.025474s |

En general note que el guided scheduling tuvo mejores resultados que los demás. Si bien la diferencia es minima, siguiendo la tendencia para valores más altos los tiempos pueden verse reducidos considerablemente. Igualmente, es interesante observar los tiempos siguen la tendencia de crecimiento con respecto al tamaño de N. Dado que el guided scheduling selecciona el tamaño del chunk desde el inicio de primera iteracion este no es asignado durante la ejecución. Por lo tanto, se pueden obtener mejores tiempos al ir disminuyendo los chunks con cada iteración. Partiendo desde N's más grandes. 


## Referencias

* Intel (Abril, 2012). _OpenMP* Loop Scheduling_. Recuperado de: https://software.intel.com/content/www/us/en/develop/articles/openmp-loop-scheduling.html

* OpenMP.org (s.f.). _OpenMP 5.0 API Syntax Reference Guide_. Recuperado de: https://www.openmp.org/resources/refguides/

* RookieHPC (s.f.) _guided_. Recuperado de: https://www.rookiehpc.com/openmp/docs/guided.php
