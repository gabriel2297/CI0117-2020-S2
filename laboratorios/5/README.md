# CI0117 - Laboratorio 5

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

### Instrucciones generales

**Fecha de entrega:** Viernes 2 de Octubre 11:50pm.

Este laboratorio se podrá realizar en grupos de máximo 2 personas.
Las soluciones a los ejercicios de este laboratorio deberán ser subidas a su repositorio *CI0117-2020-S2* creado para este curso en Github. Dentro de dicho repositorio se deberá crear un folder con el nombre *laboratorios*. La solución a cada laboratorio deberá estar contenida dentro de un folder con el respectivo número dentro del folder *laboratorios*. A su vez, la solución al ejercicio deberá subirse en un folder con el nombre indicado entre paréntesis cuadrados. 

Para los ejercicios que, además de código, también requieran responder preguntas sobre la solución, se deberá crear un archivo README.md con las respuestas dentro del folder del ejercicio respectivo.
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.
Asegúrese de subir al repositorio únicamente archivos .c, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

Únicamente uno de los integrantes del grupo requiere subir la solución.

## Ejercicio 1 [riemann_serial]
Implemente en C un método que recibe un punto *a*, un punto *b* y una cantidad *n* y aproxima serialmente el área bajo la curva de la función <img src="https://render.githubusercontent.com/render/math?math=f(x)%20=%20x^2%20%2B1"> usando la aproximación de Riemann simple con *n* rectángulos (Ver material de apoyo).
Implemente una función main() que recibe por argumentos de línea de comandos los números *a*, *b* y *n* (todos enteros positivos) e invoque el método para calcular el área bajo la curva de f siguiendo la aproximación de Riemann con rectángulos. Imprima la estimación del área en pantalla y la duración en realizar el cálculo. Asegúrese de no generar accesos inválidos ni fugas de memoria.

Puede utilizar el siguiente código para hacer los cálculos de la duración:

```c
typedef struct timespec walltime_t;

void walltime_start(walltime_t* start)
{
	clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start)
{
	walltime_t finish;
	clock_gettime(CLOCK_MONOTONIC, &finish);

	double elapsed = (finish.tv_sec - start->tv_sec);
	elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;

	return elapsed;
}
```

## Ejercicio 2 [riemann_pthreads]
Modifique su solución al ejercicio anterior para recibir un argumento adicional que indica la cantidad de trabajadores (threads) en la línea de comandos.
Modifique el método que calcula el área bajo la curva para que la estimación con los rectángulos sea distribuida entre la cantidad de threads disponible. Asegúrese de no generar fugas de memoria ni condiciones de carrera.

Ejecute los programas de ambos ejericios para *n = 1*, *n = 10*, *n = 1,000* y *n = 1,000,000* (si el hardware lo permite), utilizando los mismos valores de *a* y *b* en cada ejecución. Para el caso del programa que utiliza pthreads, realice ejeciciones usando 1, 16, 32 y 64 hilos.
Apunte la duración de cada ejecución y asegúrese de obtener las mismas áreas estimadas por la versión serial y concurrente. Agregue los datos de la comparación al archivo .md de este ejercicio. 

| a | b | n | area | serial | 1  | 16 | 32 | 64 |
|---|---|---|---|---|---|---|---|---|
| 1 | 15 | 1  |  28.000000 |  0.000002 | 0.000286  | 0.001437  | 0.003328  | 0.005201  |
| 1 | 15 | 10  | 986.440000  |  0.000003 | 0.000118 | 0.002081  | 0.002934  | 0.007093  |
| 1 | 15 | 1000  | 1137.099124  | 0.000011  | 0.000301  |  0.001108 | 0.002152  | 0.003167  |
| 1 | 15 | 1000000  | 1138.665099  | 0.006601  | 0.016304  | 0.007690  | 0.009583  | 0.011317  |
| 1 | 15 | 1000000000  | 1138.666648  | 5.457817  | 15.087422  | 6.275093  | 6.037482  |  6.208073  |
| 1 | 15 | 1000000000000  | no pudo  | 5 min+ |   |   |   |   |

### Material de apoyo:

* Aproximación de Riemann simple usando rectángulos - https://youtu.be/W1IPtvVWCr8
