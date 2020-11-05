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

[critical vs atomic - Stack Overflow](https://stackoverflow.com/questions/7798010/what-is-the-difference-between-atomic-and-critical-in-openmp#:~:text=The%20most%20important%20difference%20between,use%20it%20with%20specific%20operators.&text=Critical%20section%3A,use%20of%20%22name%22%20tag.)

[critical vs atomic - OpenMP Forum](https://forum.openmp.org/viewtopic.php?t=1549)

[omp - Microsoft C++ Docs](https://docs.microsoft.com/en-us/cpp/parallel/openmp/reference/openmp-directives?view=msvc-160#atomic)

[omp critical - IBM Knowledge center](https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/prag_omp_critical.htm)

[omp atomic - IBM Knowledge center](https://www.ibm.com/support/knowledgecenter/SSGH2K_13.1.2/com.ibm.xlc1312.aix.doc/compiler_ref/prag_omp_atomic.html)

[omp atomic - OpenMP API Specification](https://www.openmp.org/spec-html/5.0/openmpsu95.html)

