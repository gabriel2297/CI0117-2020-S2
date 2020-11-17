# CI0117 - Actividad de clase 8

### Instrucciones generales

Las soluciones a los ejercicios de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```

Agregue un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [random_number_reduce]

Escriba un programa en C o en C++ en el que se pueda ingresar en entrada estándar varios números enteros y luego cada proceso eligirá uno aleatoriamente. Para ello realice lo siguiente:

* El proceso 0 deberá solicitar la cantidad de valores enteros a ingresar
* Seguidamente el proceso 0 solicitará uno por uno los valores (se deberá crear un arreglo de enteros del tamaño especificado y los valores ingresados se irán almacenando en este arreglo).
* El proceso 0 deberá primero enviar el número de valores ingresados a todos los demás procesos (*broadcast*) para que puedan crear un arreglo/buffer de tamaño exacto.
* Seguidamente el proceso 0 enviará el arreglo con los valores ingresados a todos los procesos (*broadcast*).
* Cada proceso seleccionará aleatoriamente un número de dicho arreglo. Puede utilizar la función *rand*:

```cpp
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
...
srand(time(NULL) * my_id * 1000); /* Initialize seed */
...
int index = rand() % num_values;
```

Una vez que cada proceso seleccione el número al azar, utilice operaciones de reducción en MPI para que el proceso 0 obtenga el mínimo, el máximo y el promedio de los números elegidos por todos los procesos (*MPI_MAX, MPI_MIN, MPI_SUM*). Cada proceso imprime el número elegido, mientras que el proceso 0 imprime además los resultados de las operaciones de reducción. Puede basarse en el ejemplo [hello_mpi_ordered.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/12_MPI/mpi_ordered/hello_mpi_ordered.cpp) para que se imprima en orden y sin condiciones de carrera. 

Ejemplo de entrada y salida esperadas:

```
$ mpiexec -n 5 ./random_number_reduce
Please enter the number of values: 
5
Please enter 5 integer values: 
7789
21
335
1
2047
process 0: I chose number 1
process 0: Minimun is 1
process 0: Maximun is 7789
process 0: Average is 1692.2
process 1: I chose number 7789
process 2: I chose number 335
process 3: I chose number 1
process 4: I chose number 335
```

## Ejercicio 2 [random_number_allreduce]

Modifique el código del ejercicio anterior para que cada proceso obtenga el resultado de las operaciones de reducción. Cada proceso imprimirá si su número es el mínimo, el máximo y si es igual/menor/mayor al promedio.


Ejemplo de entrada y salida esperadas:

```
$ mpiexec -n 5 ./random_number_reduce
Please enter the number of values: 
5
Please enter 5 integer values: 
7789
21
335
1
2047
process 0: I chose number 1. It's the minimun
process 0: I chose number 1. It's less than the average (1692.2)
process 1: I chose number 7789. It's the maximun
process 1: I chose number 7789. It's greater than the average (1692.2)
process 2: I chose number 335. It's less than the average (1692.2)
process 3: I chose number 1. It's the minimun
process 3: I chose number 1. It's less than the average (1692.2)
process 4: I chose number 335. It's less than the average (1692.2)
```

