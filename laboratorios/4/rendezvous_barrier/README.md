# Laboratorio 4 - Rendezvous y Barrera con Semáforos

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

## Rendezvous
En inglés, la palabra "rendezvous" significa una reunión, entre dos personas, a un tiempo y lugar en específico. En computación, el concepto es muy similar solo que con hilos.

En este caso, dada la ejecución en paralelo de dos hilos (las personas), el patrón de sincronización especifica que en algún momento de la ejecución los hilos tendrán una "cita" o "encuentro" (la reunión), antes de esta ninguno podrá continuar su ejecución sino hasta que ambos hayan llegado.

### Pseudocódigo que permite visualizar la solución al problema de rendezvous:
```
main: 
	bLlego = 0
	aLlego = 0
	thread a 
	thread b

funcion pagarPeajeA():
	imprimir "a pago el peaje de b"

funcion pagarPeajeB():
	imprimir "b pago el peaje de a"

funcion terminarThread():
	imprimir "thread pudo terminar" 

stack de thread a:
	a.pagarPeajeB
	aLlego = 1
	bLlego.esperar
	a.terminarThread

stack de thread b:
	b.pagarPeajeA
	bLlego = 1
	aLlego.esperar
	b.terminarThread

```
**Explicación:**
- En el ejemplo anterior cada hilo debe pagar el peaje del otro para poder continuar, por lo que un hilo no puede continuar si el otro no ha hecho el pago de su peaje. Asumiendo que el hilo "b" empieza primero, "b" pagaria el peaje de "a", seguidamente notificaria a "a" de que ya llego y por último "b" esperará a que "a" pague su peaje. En este momento el CPU se desocupa y empieza a ejecutar "a". "a" entonces paga el peaje de "b" y le notifica a "b" que ya realizó el pago por lo que "b" así puede seguir su camino y terminar. En este caso, dado que "b" ya habia pagado el peaje de "a" y ya habia notificado a "a" de ello, "a" no tendrá que esperar y podrá terminar. 

### ¿Se puede presentar alguna situación de *deadlock* o *starvation*?
Dependiendo de como se realice la espera y donde se coloque el rendezvous, es posible que se presente Deadlock en el caso de que el hilo A llegue primero, por lo que su estado será cambiado a wait. Cuando B llegue aplicará el mismo proceso. Dado que A no es capaz de emitir la señal de arribo (aArrived) en este punto ninguno de los hilos será capaz de continuar.

## Barrera con semáforos
Los rendezvous tienen una limitante, y es que solo pueden utilizarse para cuando hay dos hilos y no más. En el caso de tener más de dos hilos, lo mejor es utilizar una barrera. La barrera funcionará de manera similar a como lo hace el rendezvous, solo dejando continuar la ejecución  de los hilos una vez que todos lleguen a cierto punto. Para esto se necesitarán dos primitivas de sincronización, un mutex y un semáforo.
El mutex se encargará de realizar exclusión mutua en la zona crítica. Esta zona crítica, en este caso, será el contador que utiliza el semáforo para determinar cuántos hilos han llegado a la barrera. Dado que los hilos estarán corriendo y tratando de escribir este contador, el mutex no permitirá que se generen condiciones de carrera. Por otro lado, el semáforo estará monitoreando este contador y poniendo a cada hilo a dormir una vez que lleguen a la barrera. Cuando el hilo "n" llegue, el semáforo despertará a todos los hilos y continuarán su ejecución.

## Pseudocódigo que permite visualizar la solución al problema de rendezvous:
```
main: 
	thread a 
	thread b
	thread c
	mutex mutex
	total_threads = 3
	contador = 0
	semaforo

funcion hilos:
	mutex.lock
		contador += 1
	mutex.unlock

	contador == total_threads 
		semaforo.despertar 
		
	semaforo.dormir
	semaforo.despertar
```
**Explicación:**
- En el ejemplo anterior tenemos 3 hilos y un contador inicializado en 0. Solo un hilo tomara el mutex en dado momento para acceder al contador y asi aumentarlo. Luego de soltar el mutex, el hilo verificará si ya ese contador es igual a la cantidad de hilos. De ser el hilo "n-1" o "n-2" se procederá a dormir mientras que de ser el hilo "n" se despertará al hilo anterior y cada hilo irá despertando al anterior a ellos.

## ¿Se puede presentar alguna situación de *deadlock* o *starvation*?
Así como en el caso del rendezvous, se pueden presentar un deadlock si no se despertara el hilo despues del dormir dada la naturaleza de los semáforos en donde las acciones son incrementar y reducir, por lo que si un hilo reduce el valor del semáforo y este llega a ser negativo esto quiere decir que este hilo no podrá continuar hasta que otro hilo incremente el semáforo. De manera similar, cuando este último hilo incrementa el semáforo, de haber otros hilos esperando estos pasarán primero que el hilo que los despertó.


## Simulación de la solución al problema. Al ejecutar el programa se puede observar de forma clara lo que ocurre en cada hilo. 
Se crearon dos carpetas, rendezvous y barrier_semaphore, con los archivos `rendezvous.c` y `barrier_semaphore.c` en C para demostrar cómo se simula y se ve la solución a estos problemas utilizando pthreads. Para compilar correr `make` dentro de dichas carpetas.

