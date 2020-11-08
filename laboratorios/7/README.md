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

export OMP_SCHEDULE="static,1"
perf stat ./count_primes_cyclic 100000000

Realice pruebas y anote la duración utilizando las siguientes planificaciones:

static,1
static,N
dynamic,1
dynamic,N

En este caso para escoger los valores de N se obtuvo la cantidad por defecto de hilos que el hardware permitia para la ejecución del programa. Siendo N = 4, a partir de dicho valor se realizan las pruebas con las planificaciones. A continuación se presentan las tablas que resumen los resultados obtenidos:

Para valores constantes como static, 1 y dynamic, 1 se obtuvieron los siguientes resultados:
|Planificación |   Tiempo    |
| static, 1    | 139.890527s |
| dynamic, 1   | 97.774604s  |

Para los valores de N

|Planificación                         | static, N  | dynamic, N   |
| N = cantidad de hilos                | 98.891831s | 97.307262s   |
| N = mitad del total de hilos         | 99.007316s | 99.290917s   |
| N = mitad del total de iteraciones   | 180.103404s| 185.410482s  |

Nóte que los resultados de las planificaciones que involucran valores de N como cantidad de hilos y mitad del total de hilos tardaron tiempos similares ubicandose entre los 97 y 99 segundos. Sin embargo, al incrementar N hacia el mitad del total de las iteraciones los tiempos se duplican.


