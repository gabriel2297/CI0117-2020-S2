# CI0117 - Actividad de clase 6

### Instrucciones generales

Para esta actividad deberá trabajar en el ejercicio asignado por el profesor en [este documento](https://docs.google.com/spreadsheets/d/1CAYMqI3DKZNFjAL4q8WEkS6EEm5CQm-oHUnwE2PRAwM/edit?usp=sharing) en el tab *Actividad 6*. Para su ejercicio, utilice el manual de referencia de OpenMP (o cualquier material confiable en Internet) para investigar sobre la directiva, cláusula o función que se le solicita.

Las soluciones al ejercicio de esta actividad deberán ser subidas a su repositorio personal de Github, siguiendo la siguiente estructura de folders:

```
CI0117-2020-S2/acividades/[número de actividad]/[nombre de ejercicio]/
```

#### [omp_atomic]
Explique en un archivo .md la diferencia entre las directivas *omp critical* y *omp atomic*. Liste cuáles son los casos en los que se puede utilizar *omp atomic*. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_critical_named]
Explique en un archivo .md en qué consiste la opción de agregar un nombre a la directiva de exclusión mutua *omp critical(name)*. ¿Cuál es la diferencia con respecto a utilizarla sin agregar dicho nombre. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_barrier]
Explique en un archivo .md cómo funciona la directiva *omp barrier*. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_lock]
Explique en un archivo .md cómo funciona la directiva *omp lock*. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_for]
Explique en un archivo .md cómo funciona la directiva *omp for* (note que es diferente a *omp parallel for*) y en qué condiciones se puede utilizar. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_do]
Explique en un archivo .md cómo funciona la directiva *omp do*. Agregue un pequeño programa en C o C++ que incluya esta directiva como ejemplo.

#### [omp_get_max_threads]
Explique en un archivo .md en qué consiste la función *omp_get_max_threads*. Implemente un pequeño programa en C o C++ que incluya esta función como ejemplo e imprima en consola el valor retornado.

### Material de apoyo
- OpenMP - Manuales de Referencia: https://www.openmp.org/resources/refguides/

