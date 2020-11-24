# CI0117 - Actividad de clase 9

### Instrucciones generales

Las soluciones a los ejercicios de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```

Agregue un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [dna_sequence_mpi]

Comprenda la solución serial al problema de conteo de caracteres en una secuencia de *ADN mutante* implementada en el archivo [dna_sequence_serial.cpp](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/16_MPI/dna_sequences_serial/dna_sequences_serial.cpp). Modifique dicha solución para que el conteo se realice de forma paralela entre diferentes procesos utilizando funciones MPI, tomando en cuenta que las secuencias de ADN pueden llegar a tener una longitud de hasta 10^8 caracteres. Asegúrese de que la solución sea lo más óptima posible (por ej. evitar serializar el trabajo entre procesos o recorrer la secuencia más de lo necesario).

Considere lo siguiente:

* Todos los procesos deberían ser capaces de leer un archivo (a diferencia de leer de la entrada estándar lo cual solo se le permite al proceso 0). Sin embargo, asegúrese de que para esta solución paralela sólamente el proceso 0 lea la secuencia de ADN desde el archivo con el nombre enviado como parámetro. Puede asumir que el archivo de texto contiene únicamente una secuencia de ADN.

* El proceso 0 deberá distribuir la secuencia en segmentos más pequeños y de manera uniforme hacia los demás procesos. Utilice MPI_Scatter para dicho propósito. Recuerde que MPI_Scatter espera que todos los procesos reciban segmentos de exactamente el mismo tamaño, por lo que su solución debe considerar el caso en el que el tamaño de la secuencia no sea divisible entre el número de procesos (puede hacer que el proceso 0 se encarge del conteo de su segmento y de los caracteres restantes).

* Utilice cualquier otra función de comunicación colectiva vista en clase que considere necesaria para procesar resultados o para enviar mensajes entre procesos.

* Asegúrese de que el resultado sea el mismo obtenido por la solución serial cuando se utiliza la misma secuencia de ADN.

* Puede usar las secuencias de los archivos de texto de ejemplo en el folder [dna_sequence_serial](https://github.com/jocan3/CI9117-2020-S2/tree/master/Ejemplos%20de%20clase/16_MPI/dna_sequences_serial) (el archivo *sequence2.txt* contiene una secuencia de 98,991,090 caracteres, por lo que se recomienda no intentar abrirlo con un editor).

* Utilice el archivo *sequence2.txt* para jugar con el número de procesos y el tiempo de ejecución de su programa (por ejemplo, utilizando *perf stat* o alguna otra función para calcular la duración). Intente encontrar el número de procesos "óptimo" en su máquina que logre una mejor duración con respecto a la solución serial (Note que más procesos no necesariamente implica mejor duración).

## Ejercicio 1 [dna_sequence_mpi_hyb]

Se pueden implementar programas "híbridos" que combinen tanto paralelismo entre procesos como paralelismo entre hilos. Modifique su solución al ejericicio 1 de esta actividad para que cada proceso internamente paralelice el conteo de caracteres utilizando hilos. Realice esto utilizando directivas de OpenMP vistas en clase. Asegúrese de especificar el *scope* de las variables a utilizar dentro del bloque paralelo.




