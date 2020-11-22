# CI0117 - Laboratorio 8

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

### Instrucciones generales

**Fecha de entrega:** Lunes 23 de Noviembre 11:50pm.

Este laboratorio se podrá realizar en grupos de máximo 2 personas.
Las soluciones a los ejercicios de este laboratorio deberán ser subidas a su repositorio *CI0117-2020-S2* creado para este curso en Github. Dentro de dicho repositorio se deberá crear un folder con el nombre *laboratorios*. La solución a cada laboratorio deberá estar contenida dentro de un folder con el respectivo número dentro del folder *laboratorios*. A su vez, la solución al ejercicio deberá subirse en un folder con el nombre indicado entre paréntesis cuadrados.
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.

Las soluciones o respuestas que no son código, deberán estar en un archivo .md en el folder del ejercicio respectivo. Asegúrese de subir al repositorio únicamente archivos .c/.cpp, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

Únicamente uno de los integrantes del grupo requiere subir la solución. **Indique en el archivo README.md el nombre de ambos integrantes**.

## Ejercicio 1 [count_primes_process]

Modifique su solución al problema de conteo de primos paralelo implementado en el laboratorio anterior (**count_primes_parallel**) para que la paralización se realice a nivel de procesos. De igual manera, el programa debe calcular cantidad de números primos entre 2 y un número dado como primer argumento en la línea de comandos.

Utilice únicamente comunicación punto a punto (*MPI_Send* y *MPI_Recv*). Cada proceso calculará el rango a procesar basándose en su id (rank), realizará el conteo y luego enviará el resultado al proceso 0. El proceso 0 recibirá uno por uno los resultados y los sumará para obtener el resultado final.

Investigue sobre la función MPI_Wtime y utilícela para calcular el tiempo que tardan los procesos en realizar el conteo.

El proceso 0 deberá imprimir el resultado final de la siguiente manera:

```
$ mpiexec -n 6 ./count_primes_process 20
8 primes found in range [2, 20] in 0.000584510112s with 6 processes
```

## Ejercicio 2 [count_primes_reduction]

Modifique el programa del ejercicio anterior para que la suma de conteo de números primos se haga mediante una reducción de MPI. Haga también que el número se reciba en la entrada estándar y que el proceso 0 lo comunique mediante broadcast a los demás procesos. Asegúrese de que el programa produzca la misma salida.

Utilice la función MPI_Wtime para calcular el tiempo que tardan los procesos en realizar el conteo (No tome en cuenta el tiempo que se tarda leyendo de la entrada estándar).

## Ejercicio 3 [count_primes_all_reduce]

Modifique el programa del ejercicio 2 para que todos los procesos reciban el resultado de la operación de reducción de la suma del conteo de números primos. Cada proceso imprime el rango en el que trabajó, la cantidad de primos encontrados en ese rango, el total encontrado por todos los procesos y el tiempo (no importa el orden en que impriman). Ejemplo:

```
$ mpiexec -n 3 ./count_primes_all_reduce 20
process 0: 4 out of 8 primes found in range [2, 8] in 0.000584510112s with 3 processes
process 2: 2 out of 8 primes found in range [15, 20] in 0.000674510112s with 3 processes
process 1: 2 out of 8 primes found in range [9, 14] in 0.000533454323s with 3 processes
```

Haga cuatro corridas de cada solución a los ejercicios 1, 2 y 3 de este laboratorio utilizando 1, 16, 32 y 64  procesos (Puede aumentar o disminuir la cantidad de procesos dependiendo de la capacidad de su hardware). Use un rango grande de primos, similar al utilizado en el laboratorio anterior.

Agregue la tabla comparativa de tiempos en un archivo README.md. Para el ejercicio 3 sólamente tome en cuenta el tiempo que tarda el proceso 0.

