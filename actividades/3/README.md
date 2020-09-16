# CI0117 - Actividad de clase 3

### Instrucciones generales

Las soluciones a los ejercicios de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.
Asegúrese de subir al repositorio únicamente archivos .c, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [array_thrsafe_mutex]

Modifique el arreglo dinámico en C visto en clase para que sea thread-safe. Proteja la implementación de cada subrutina pública con un mutex. Note que las subrutinas para incrementar y reducir la capacidad son privadas (no están declaradas en el encabezado .h). El mutex debe ser único para cada instancia de un arreglo, es decir, dos instancias del arreglo no comparten el mismo mutex.

Utilice este código para probar su solución: [main.c](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/05_Pthreads/array_mutex/main.c)

## Ejercicio 2 [array_thrsafe_rwlock]

Provea una segunda implementación thread-safe del arreglo dinámico en C. Provea un candado de lectura y escritura (pthread_rwlock_t) para cada instancia del arreglo dinámico. Proteja el código de cada subrutina que no modifica el arreglo bloqueando el candado para lectura. De la misma forma proteja el código de cada subrutina que modifica bloqueando el candado para escritura.

Utilice este código para probar su solución: [main.c](https://github.com/jocan3/CI9117-2020-S2/blob/master/Ejemplos%20de%20clase/05_Pthreads/array_mutex/main.c)

Ejemplo de uso de pthread_rwlock_t:

```c
// Declare
pthread_rwlock_t rwlock;

// Init & destroy
pthread_rwlock_init( &rwlock, NULL );
pthread_rwlock_destroy( &rwlock );

// Lock for read
pthread_rwlock_rdlock( &rwlock );

// Lock for write
pthread_rwlock_wrlock( &rwlock );

// Unlock
pthread_rwlock_unlock( &rwlock );

```
