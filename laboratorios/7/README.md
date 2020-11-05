# CI0117 - Laboratorio 7

## Estudiantes:
- Emmanuel Zúñiga Chaves (B98729)
- Gabriel Umaña Frías (C09913)

### Instrucciones generales

**Fecha de entrega:** Lunes 9 de Noviembre 11:50pm.

Este laboratorio se podrá realizar en grupos de máximo 2 personas.
Las soluciones a los ejercicios de este laboratorio deberán ser subidas a su repositorio *CI0117-2020-S2* creado para este curso en Github. Dentro de dicho repositorio se deberá crear un folder con el nombre *laboratorios*. La solución a cada laboratorio deberá estar contenida dentro de un folder con el respectivo número dentro del folder *laboratorios*. A su vez, la solución al ejercicio deberá subirse en un folder con el nombre indicado entre paréntesis cuadrados. 
Agregue un archivo *Makefile* para cada uno de los ejercicios con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el mismo nombre dado en el ejercicio.

Las soluciones o respuestas que no son código, deberán estar en un archivo .md en el folder del ejercicio respectivo. Asegúrese de subir al repositorio únicamente archivos .c, .md y Makefile. Cree un archivo .gitignore para evitar subir archivos ejecutables.

Únicamente uno de los integrantes del grupo requiere subir la solución. **Indique en el archivo README.md el nombre de ambos integrantes**.

## Ejercicio 1 [count_primes_serial]

Implemente un programa en C o en C++ que cuente de forma serial la cantidad de números primos entre 2 y un número dado como primer argumento en la línea de comandos. Dicho programa **no** debe utilizar programación paralela.

Puede utilizar la siguiente logica para determinar si un número es primo:

```c
	if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;
```

Calcule el tiempo que se tarda en correr el programa para un número grande de n, por ejemplo 100 millones (o similar, dependiendo de lo que permita el hardware). Puede instalar la herramienta de profiling *perf* de linux para calcular este tiempo:

```
$ perf stat ./count_primes_serial 100000000
```

## Ejercicio 2 [count_primes_parallel]

Modifique el programa del ejercicio anterior para que la solución se realice de forma paralela utilizando *parallel for* de OpenMP. Utilice *reduction* en lugar de declarar zonas críticas y especifique el *scope* de las variables. Puede utilizar la cantidad de hilos por defecto (o sea, no es necesario especificar el número de hilos con *num_threads*).

Anote el incremento de velocidad obtenido con respecto al programa del ejercicio anterior.

## Ejercicio 3 [count_primes_cyclic]

Modifique el código del programa del ejercicio 2 para que las iteraciones se distribuyan entre los hilos utilizando *scheduling* en tiempo de ejecución (*runtime*). De forma que desde la línea de comandos, antes de ejecutar el programa se modifique la variable de ambiente *OMP_SCHEDULE* con el valor de diferentes tipos de *scheduling*. Por ejemplo:

```
export OMP_SCHEDULE="static,1"
perf stat ./count_primes_cyclic 100000000
```

Realice pruebas y anote la duración utilizando las siguientes planificaciones:

```
static,1
static,N
dynamic,1
dynamic,N
```
Para el valor de N, utilice los siguientes casos: N = cantidad de hilos, N = mitad del total de hilos, N = mitad del total de iteraciones. 

Investigue sobre el tipo de *scheduling* guiado (*guided*). Explique cómo funciona este tipo de planificación (Incluya un ejemplo). De igual forma, realice pruebas utilizando este tipo de planificación con valores de 1 y N similar a las realizadas para *static* y *dynamic*. Anote las duraciones.

Muestre una tabla con todos los resultados de tiempos obtenidos luego de realizar las pruebas anteriores. Resalte cuál tipo de *scheduling* obtuvo mejor rendimiento y escriba un comentario que explique por qué considera que se obtuvo el resultado.

### Material de apoyo:

* OpenMP - Manuales de Referencia: https://www.openmp.org/resources/refguides/ 