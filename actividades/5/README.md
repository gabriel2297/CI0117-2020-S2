# CI0117 - Actividad de clase 5

### Instrucciones generales

Las soluciones al ejercicio de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```

Agregue un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [average_parallel]

Modifique el código de la solución [average.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/09_OpenMP/average_serial/average.cpp) para que el cálculo de la sumatoria se realice de forma paralela utilizando únicamente las siguiente directivas de OpenMP:

```cpp
omp parallel
omp critical
```

El número de hilos a utilizar se definirá como una constante en en método *main* y puede realizar alguna validación para que la cantidad de valores pasados como parámetro sea múltiplo de dicha constante. El programa deberá imprimir el número de hilo y el número de la lista que está siendo procesado, así como el resultado del promedio final. Por ejemplo:

```
$ ./average 10 20 30 40 50 60
Thread 0: Processing number 10
Thread 1: Processing number 30
Thread 2: Processing number 50
Thread 0: Processing number 20
Thread 2: Processing number 60
Thread 1: Processing number 40
Average: 35
```

Para lograr lo anterior, realice lo siguiente:

* Substituya el ciclo *for* del método *main* por una región paralela utilizando *omp parallel* y la cláusula *num_threads*. El bloque de código paralelo únicamente llamará a una función *calculate_sum* que definiremos como parte de este ejercicio.

* Implemente un método *calculate_sum* que reciba como parámetro un arreglo de strings, el tamaño del arreglo y un puntero a un resultado global. 

```cpp
static void calculate_sum(char **array, int array_size, double* global_sum) {
  //...
}
```
Este método deberá calcular la sección del arreglo que va a procesar cada hilo y realizar una sumatoria local en un ciclo para los números de dicha sección. Por último sumará dicho valor a la variable global *global_sum*. Utilice las funciones de OpenMP para obtener el número de hilo y la cantidad total de hilos. Asegúrese de proteger/sincronizar el acceso a la memoria compartida.

**Opcional:** Modifique su código para que el número de hilos a utilizar corresponda al primer valor del arreglo y elimine la validación de que la cantidad de valores sera múltiplo del número de hilos. O sea, que funcione para cualquier cantidad de hilos y tamaño de arreglo.

## Ejercicio 2[average_parallel_for]

Realice las modificaciones necesarias al ejercicio anterior para que se utilice la directiva:

```cpp
omp parallel for
```
El programa debe imprimir la misma información y debe asegurarse de sincronizar el acceso a la memoria compartida.

