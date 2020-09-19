# Laboratorio 4 - Rendezvous y Barrera con Semáforos

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

## Descripción del problema / patrón de sincronización.
### Rendezvous
Dada la ejecución en paralelo de dos hilos, el patrón de sincronización especifica que en algún momento de la ejecución ambos hilos tendrán una "cita" o "encuentro" y ninguno puede continuar hasta que los dos hayan llegado.
### Barrera con semáforos
## ¿Se puede presentar alguna situación de *deadlock* o *starvation*?
Es posible que se presente Deadlock, en el caso de que el hilo A llegué primero su estado será cambiado a wait, cuando B llegúe aplicará el mismo proceso. Dado que A no es capaz de emitir la señal de arribo (aArrived) en este punto ninguno de los hilos será capaz de continuar. 
## Pseudocódigo que permite visualizar la solución al problema:
```
void * rendezvous_Thread(void * args){
	statement a1;
	aArrived.signal();
	bArrived.wait();
	statement a2;

	return NULL;
}
```
## Simulación de la solución al problema. Al ejecutar el programa se puede observar de forma clara lo que ocurre en cada hilo. 
Se creó el archivo `rendezvous_barrier.c` en C para demostrar cómo se simula y se ve la solución a estos problemas utilizando pthreads.
Para compilar correr `make`.

