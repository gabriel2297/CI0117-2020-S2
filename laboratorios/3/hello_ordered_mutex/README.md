## Ejercicio 2 [hello_ordered_mutex]

- NOTA: profe, este lo intente muchisimo pero nada... compila, pero llega hasta la cantidad indicada - 2... Nunca a la cantidad indicada y no entiendo por que.. 

Modifique la solución del ejemplo de Hello Word con espera activa visto en clase para obligar a los hilos de ejecución a saludar en orden en la salida estándar. Use una colección de mutexes, uno por cada thread. Haga que únicamente el thread 0 tenga su mutex habilitado. Cuando el thread 0 ha saludado, habilita el mutex del siguiente thread y así sucesivamente.
Corra su solución y mida el tiempo de ejecución. ¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible?
- Si, dado que los hilos van avisando uno al otro que ya es hora de correr.