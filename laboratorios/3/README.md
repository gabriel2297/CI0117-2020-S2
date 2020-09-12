# CI0117 - Laboratorio 3

### Instrucciones generales

**Fecha de entrega:** Viernes 11 de Setiembre.

Las soluciones a los ejercicios de este laboratorio deberán ser subidas a un repositorio público de Github. Para ello el estudiante deberá tener una cuenta en https://github.com/ y crear un repositorio público con el nombre *CI0117-2020-S2*. Dentro de dicho repositorio se deberá crear un folder con el nombre *laboratorios*. La solución a cada laboratorio deberá estar contenida dentro de un folder con el respectivo número dentro del folder *laboratorios*. A su vez, la solución a cada ejercicio deberá subirse en un folder con el nombre indicado entre paréntesis cuadrados. Por ejemplo, para el **Ejercicio 1**, el código de la solución deberá entregarse siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/laboratorios/3/thread_creation_time/thread_creation_time.c
```

Para los ejercicios que, además de código, también requieran responder preguntas sobre la solución, se deberá crear un archivo README.md con las respuestas dentro del folder del ejercicio respectivo.
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.
Asegúrese de subir al repositorio únicamente archivos .c, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

## Ejercicio 1 [thread_creation_time]

Estime el tiempo que toma el sistema en crear y destruir un thread. Escriba un programa en C que reciba un número entero T en los argumentos de línea de comandos, el cual indica la cantidad de pruebas a realizar. Si el usuario no especifica este número, asuma T = 1.
Seguidamente su programa realiza T pruebas secuenciales. En cada prueba, el thread principal crea un thread secundario, espera a que este termine, y mide la duración que tardan estas dos acciones juntas con resolución de nanosegundos. El thread secundario simplemente ejecuta una función cuyo cuerpo es vacío. Note que las pruebas no se realizan concurrente si no secuencialmente.
El thread principal debe reportar una estadística en la salida estándar, que es la duración en segundos de la prueba que tardó menos tiempo. Este dato permite a un programador tener un estimado del tiempo en que tarda el sistema en crear y destruir un hilo de ejecución. La salida podría tener el formato:

```
Minimum thread creation and destruction time was 0.123456789s among 12345 trials
```

*Sugerencia:* Utilice la función *clock_gettime* para obtener el tiempo inicial y final y calcular la duración.

## Ejercicio 2 [hello_ordered_mutex]

Modifique la solución del ejemplo de Hello Word con espera activa visto en clase para obligar a los hilos de ejecución a saludar en orden en la salida estándar. Use una colección de mutexes, uno por cada thread. Haga que únicamente el thread 0 tenga su mutex habilitado. Cuando el thread 0 ha saludado, habilita el mutex del siguiente thread y así sucesivamente.
Corra su solución y mida el tiempo de ejecución. ¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible?

## Ejercicio 3 [hello_ordered_semaphore]

Modifique su solución al ejercicio hello_ordered_mutex para que en lugar de usar exclusión mutua (mutex), use un arreglo de semáforos, uno por cada thread.
Corra su solución y mida el tiempo de ejecución. ¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible? Explique las diferencias entre usar exclusión mutua y semáforos para resolver este problema en un archivo rationale.md dentro de su carpeta hello_ordered_semaphore.


### Material de apoyo:

* Comandos básicos de git: https://education.github.com/git-cheat-sheet-education.pdf









