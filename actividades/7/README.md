# CI0117 - Actividad de clase 7

### Instrucciones generales

Las soluciones a los ejercicios de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```

Agregue un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [hello_mpi_ordered_for]

Modifique el código de la solución [hello_mpi_rank.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/11_MPI/hello_mpi_rank/hello_mpi_rank.cpp) para que los procesos impriman su saludo en orden por su identificador (rank). Use comunicación punto a punto (*send* y *receive*), de forma que el procesco 0 ejecute un ciclo *for* y vaya "avisando" a cada uno de los siguientes procesos cuando les corresponda saludar.

Ejemplos de uso de MPI_Send y MPI_Recv

```cpp
MPI_Send(&message_sent, 1 /*count*/, MPI_INT, 1 /*dest*/, 123 /*message id*/, MPI_COMM_WORLD);

MPI_Recv(&message_received, 1 /* count*/, MPI_INT, 0 /*source*/, 123 /*message id*/, MPI_COMM_WORLD, &status);
```

## Ejercicio 2 [hello_mpi_ordered]

Modifique el código de la solución [hello_mpi_rank.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/11_MPI/hello_mpi_rank/hello_mpi_rank.cpp) para que los procesos impriman su saludo en orden por su identificador (rank). Use comunicación punto a punto (*send* y *receive*) pero sin utilizar ningún ciclo *for*, sino que los procesos se sicronicen entre ellos.

## Ejercicio 3 [hello_mpi_race]

Modifique el código de la solución [hello_mpi_rank.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/11_MPI/hello_mpi_rank/hello_mpi_rank.cpp) para que los procesos impriman su saludo en el orden en que terminan de ejecutarse. Use comunicación punto a punto (*send* y *receive*). Haga que el proceso 0 sea el "referi" de la carrera: los demás procesos saludan al proceso 0 y éste reporta los saludos en el orden en que los recibió. Utilice MPI_ANY_SOURCE al recibir mensajes para lograr esto.
