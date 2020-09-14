# CI0117 - Actividad de clase 2

### Instrucciones generales

Las soluciones a los ejercicios de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.
Asegúrese de subir al repositorio únicamente archivos .c, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [position_race_barrier]

En el ejercicio *position_race* implementado en la actividad 1, se realizó una carrera de hilos donde cada hilo imprimía su posición. Sin embargo, esto podría verse un poco "injusto" para algunos hilos, ya que los que fueron creados de primero podrían tener ventaja y terminar la carrera antes de que todos los hilos se hayan creado.
Modifique su solución para implementar una línea de salida, de modo que los hilos empiecen la carrera hasta que todos estén listos. Cada hilo imprimirá cuando esté listo y cuando haya llegado a la meta.

Haga que cada hilo tarde un tiempo aleatorio en prepararse antes de llegar a la línea de salida. Para ello puede utilizar el siguiente método para realizar un *sleep* de tiempo aleatorio:

```c
void random_sleep(useconds_t min_milliseconds, useconds_t max_milliseconds)
{
	useconds_t duration = min_milliseconds;
	useconds_t range = max_milliseconds - min_milliseconds;
	if ( range > 0 )
		duration += rand() % range;
	usleep( 1000 * duration );
}
```
**Sugerencia:** Utilice *srand( time(NULL) );* al inicio del método main para lograr que los números aleatorios varíen durante cada ejecución.

Implemente la línea de salida como un *barrier*.

```c
pthread_barrier_t barrier_example;
size_t value = 10;
pthread_barrier_init(&barrier_example, /*attr*/ NULL, value);
...
pthread_barrier_wait(&barrier_example);
```

Ejemplo de salida esperada:

```
$ ./position_race_barrier 5
Thread 4/5: I am ready!
Thread 1/5: I am ready!
Thread 2/5: I am ready!
Thread 0/5: I am ready!
Thread 3/5: I am ready!
Thread 3/5: I arrived at position 1
Thread 0/5: I arrived at position 2
Thread 4/5: I arrived at position 3
Thread 1/5: I arrived at position 4
Thread 2/5: I arrived at position 5
```

