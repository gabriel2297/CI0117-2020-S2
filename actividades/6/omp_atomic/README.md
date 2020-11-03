# CI0117 - Lab 6: [omp_atomic]

## Estudiantes:
- Emmanuel Zúñiga Chaves (B98729)
- Gabriel Umaña Frías (C09913)

### OMP atomic

La directiva `#pragma omp atomic` es una directiva brindada por la API de OpenMP para realizar operaciones de manera atomica, es decir, que se garantice la lectura o escritura de una region de memoria en particular sin tener condiciones de carrera.

Diferencias: 

| critical |  atomic  |
| -------- | -------- |
| Es muy lento dado que cada hilo bloqueara la region critica, evitando que otros hilos puedan usarla | Mucho mas rapido, dado que no hay lock/unlock de la parte del codigo a la que se quiere entrar|
| Garantiza la serializacion de una parte de codigo | Garantiza la serializacion de una operacion en particular |
| No permite que diversos hilos entren a la misma region | Permite que diversos hilos realicen modificaciones a diferentes elementos de (por ejemplo) un arreglo, de manera concurrente |
| No toma ventaja del hardware para optimizacion | Toma ventaja del hardware para realizar optimizacion, por que el hardware indica que la operacion es atomica y no se puede interferir. 

### Referencias

