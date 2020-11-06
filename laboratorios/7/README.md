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

