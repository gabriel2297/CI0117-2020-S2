# CI0117 - Proyecto 2: *Battle Royale* de Procesos [super_mario_mpi]

### Instrucciones generales

**Fecha de entrega:** Viernes 4 de Diciembre 11:50pm.

### Introducción

En este proyecto se implementará un [*battle royale*](https://es.wikipedia.org/wiki/Battle_royale_(videojuegos)#:~:text=1%20Concepto-,Concepto,a%20todos%20los%20dem%C3%A1s%20oponentes.) entre procesos, simulando una versión muy simplificada del juego [Super Mario Bross 35](https://www.nintendo.com/games/detail/super-mario-bros-35-switch/). Para ello se creará un programa en C++ o en C donde un jugador virtual simulará el recorrido de Mario a lo largo del primer mundo (1-1) de su versión original. Dicho programa deberá poder ejecutarse utilizando el estándar de Message Passing Interface (MPI) de forma que se puedan tener varios procesos simultáneamente simulando el juego e interactuando entre ellos. Puede ver un *gameplay* del juego Super Mario Bross 35 [aquí](https://www.youtube.com/watch?v=Z05l1bkDSbM&ab_channel=Jos%C3%A9Andr%C3%A9sMena).

### Requerimientos de implementación

* El programa debe contener todas las validaciones necesarias, principalmente para los valores ingresados por el usuario, de forma que se mantenga la integridad de la ejecución y se cumpla con los requerimientos.
* La estructura y código del programa deben seguir buenas prácticas y se evaluará *clean code*: Aprovechamiento de orientación a objetos, separación de responsabilidades, métodos simples, no repetición de código, no uso variables globales y documentación interna.
* No hay un límite sobre el número de procesos simultáneos, pero puede asumir que la funcionalidad se evaluará con más de 3 procesos y menos de 35.
* El proceso 0 no será un jugador, sino que se utilizará como apoyo general del programa (i.e. obtención de inputs del usuario, anuncio del ganador, etc.). Los procesos del 1 al N serán jugadores del *battle royale*.
* Toda la comunicación entre procesos se realizará utilizando MPI. Pueden usar cualquier función disponible del estándar MPI necesaria para lograr la funcionalidad y comunicación colectiva entre procesos: MPI_Bcast, MPI_Reduce, MPI_Scatter, MPI_Gather, MPI_Allgather, etc.
* Asegúrense de no generar accesos inválidos ni fugas de memoria.
* Este proyecto no requerirá tener una interfaz gráfica y la interacción (entradas y salidas) se podrá realizar siempre desde la terminal de línea de comandos.
* El recorrido de Mario dentro de la simulación se limitará únicamente al primer mundo (1-1). Puede basarse en [esta imagen](http://www.mariouniverse.com/wp-content/img/maps/nes/smb/1-1.png) para representarlo en su programa. Éste se representará como un arreglo/lista que se recorrerá de forma cicular.
* Los elementos del mundo de Super Mario a considerar para este proyecto son: *coin*, *little goomba*, *koopa troopa* y *hole* (ver detalles más adelante).
* Las acciones de Mario se limitarán a las necesarias para interactuar con dichos objetos. Implemente la lógica necesaria para elegir la acción realizada basándose en probablidades.

### Requerimientos de la simulación

#### Mundo
El mundo podrá ser representado como una colección de casillas (*slots*) donde cada casilla contiene cero o más elementos. Puede basarse en [esta imagen](http://www.mariouniverse.com/wp-content/img/maps/nes/smb/1-1.png) para representar el mundo en su programa. Por ejemplo, las primeras 40 casillas del mundo podrían distribuirse de la siguiente manera:

![Mario World Array](http://jocan3.com/misc_images/mario_world_array.png)

0 = empty |
1 = empty |
2 = empty |
3 = empty |
4 = empty |
5 = empty |
6 = empty |
7 = empty |
8 = empty |
9 = coin |
10 = empty |
11 = empty |
12 = [little_goomba, coin, coin] |
13 = empty |
14 = empty |
15 = empty |
16 = empty |
17 = empty |
18 = empty |
19 = empty |
20 = empty |
21 = [little_goomba] |
... |
26 = [little_goomba] |
27 = [little_goomba] |
... |
35 = [hole] |
36 = [hole] |
... |

Note que no todos los elementos de la imagen serán requeridos para efectos de este proyecto. Cuando Mario llega al final del mundo (Bandera), éste volverá a empezar desde la casilla 0.

#### Elementos del Mundo

![Coin](http://jocan3.com/misc_images/coin.png) *coin*

Representa un bloque flotante con signo de interrogación. Cuando Mario encuentra este elemento, pueden suceder las siguientes acciones:

* Mario no salta (Probabilidad 0.5). Esta acción no tienen ningún efecto.
* Mario salta y golpea el bloque (Probabilidad 0.5). Mario obtiene una moneda.

![Hole](http://jocan3.com/misc_images/hole.png) *hole*

Representa un hoyo en el camino. Cuando Mario encuentra este elemento, pueden suceder las siguientes acciones:

* Mario no salta (Probabilidad 0.05). Mario cae y el juego termina (Game Over).
* Mario salta y pasa (Probabilidad 0.95). Esta acción no tienen ningún efecto.

![Litte goomba](http://jocan3.com/misc_images/goomba.png) *little goomba*

Representa un enemigo. Cuando Mario encuentra este elemento, pueden suceder las siguientes acciones:

* Mario no salta (Probabilidad 0.05). Mario muere y el juego termina (Game Over).
* Mario salta y pasa (Probabilidad 0.55). Esta acción no tienen ningún efecto.
* Mario salta y mata al enemigo (Probabilidad 0.40). Esta acción tiene efectos descritos más adelante.

![koopa troopa](http://jocan3.com/misc_images/koopa_troopa.png) *koopa troopa*

Representa un enemigo. Cuando Mario encuentra este elemento, pueden suceder las siguientes acciones:

* Mario no salta (Probabilidad 0.10). Mario muere y el juego termina (Game Over).
* Mario salta y pasa (Probabilidad 0.53). Esta acción no tienen ningún efecto.
* Mario salta y mata al enemigo (Probabilidad 0.37). Esta acción tiene efectos descritos más adelante.

#### Mario
Mario representa al jugador. Tendrá un atributo número de monedas que inicialmente estará en 0. Mientras el jugador esté *activo*, Mario se irá moviendo por las casillas del mundo. En el momento en que la casilla tenga elementos, Mario deberá realizar una acción sobre cada uno de los elementos en esa casilla (sólamente podrá realizar acciones que sean posibles sobre el elemento y basándose en la probabilidad especificada en la sección anterior).

Observe que no se considerarán elementos tales como hongos, por lo que Mario sólamente tiene una vida. En el momento que ocurra un fin de juego (Game Over), Mario no podrá continuar jugando y el jugador pasará a estado *inactivo*.

El programa deberá mostrar en todo momento cada una de las acciones de Mario, la casilla del Mundo en la que se encuentra y sus atributos. Por ejemplo:

```
World pos. 7: Mario is walking. Coins: 0
World pos. 8: Mario is walking. Coins: 0
World pos. 9: Mario jumped and grabbed a coin!. Coins: 0
World pos. 10: Mario is walking. Coins: 1
World pos. 11: Mario is walking. Coins: 1
World pos. 12: Mario jumped and grabbed a coin!. Coins: 1
World pos. 12: Mario didn't grab a coin. Coins: 2
World pos. 12: Mario didn't jump and was killed by a little goomba. Coins: 2
Game Over.
```

Note que esta salida no debe ser la salida del programa final ya que no incluye informacion sobre la interacción con otros procesos (ver siguiente sección).

### Requerimientos del Battle Royale

* Varios jugadores (procesos) estarán ejecutando la simulación al mismo tiempo. Cada uno tendrá su propio Mundo y su propio Mario.
* Cuando un jugador A ataca a un jugador B, significa que todos los enemigos que A elimine en su mundo serán enviados al mundo de B. Por ejemplo, si Mario del jugador A mata a un *little goomba*, entonces en el mundo del jugador B aparecerá un *little goomba* extra (este **aparecerá 10 casillas adelante** con respecto a la posición actual de Mario del jugador B).
* En todo momento, cada jugador activo deberá estar siempre atacando a otro jugador activo.
* Hay 4 estrategias para atacar:
  * R. aleatorio (*random*): Jugador A ataca aleatoriamente a un jugador activo B cada vez que elimina un enemigo.
  * L. menos monedas (*less coins*): Jugador A ataca siempre al jugador activo que tenga menos monedas (si hay empate, se elige solamente 1).
  * M. más monedas (*more coins*): Jugador A ataca siempre al jugador activo que tenga más monedas (si hay empate, se elige solamente 1).
  * A. atacante (*attacker*): Jugador A ataca a uno de los jugadores atacantes cada vez que elimina un enemigo (si no hay atacantes, se elije aleatoriamente a un jugador activo B)
* La estrategia a utilizar se elige aleatoriamente para cada jugador antes de iniciar.
* Durante una partida sólamente se mostrará la información de la simulación de un jugador. Dicha información debe incluir el atacante y el objetivo, su estrategia de ataque, así como el total jugadores activos. El usuario elige cuál jugador visualizar al ejecutar el programa y cuál será la estrategia de ataque para ese jugador. Por ejemplo:

```
$ mpiexec -n 5 ./super_mario_mpi 2 R
World pos. 0: Mario #2 is walking. Coins: 0 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 1: Mario #2 is walking. Coins: 0 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 2: Mario #2 is walking. Coins: 0 | atacking #1 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 3: Mario #2 is walking. Coins: 0 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 4: Mario #2 is walking. Coins: 0 | atacking #1 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 5: Mario #2 is walking. Coins: 0 | atacking #4 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 6: Mario #2 is walking. Coins: 0 | atacking #4 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 7: Mario #2 is walking. Coins: 0 | atacking #4 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 8: Mario #2 is walking. Coins: 0 | atacking #5 | being attacked by #5 | attack strategy: RANDOM | Total playing: 4
World pos. 9: Mario #2 jumped and grabbed a coin!. Coins: 0 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 10: Mario #2 is walking. Coins: 1 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 11: Mario #2 is walking. Coins: 1 | atacking #2 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 12: Mario #2 jumped and grabbed a coin!. Coins: 1 | atacking #3 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 12: Mario #2 didn't grab a coin. Coins: 2 | atacking #4 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 12: Mario #2 didn't jump and was killed by a little goomba. Coins: 2 | atacking #5 | being attacked by #5 | attack strategy: RANDOM | Total playing: 3
World pos. 12: Mario #2 Game Over.
```
* Si el jugador siendo mostrado termina (Game Over), el programa debe pedir al usuario indicar otro número de jugador activo para mostrar.
* Cuando sólamente queda 1 jugador activo, la batalla (programa) termina y dicho jugador es anunciado como el ganador

### Documentación

La documentación del proyecto debe contener las siguientes secciones:

* Manual de usuario: Incluir información sobre cómo compilar el código fuente y bibliotecas adicionales a instalar. Información sobre cómo utilizar el programa (entradas esperadas e interpretación de resultados).

* Detalles de la solución: Estructura del programa (clases, folders, archivos, etc.) y breve descripción de cada uno de los componentes. Puede agregar un diagrama de componentes para representar la interacción entre los elementos.

* MPI: Para cada una de las funciones del estándar MPI utilizadas, explique brevemente su función dentro del programa.

### Evaluación
* Funcionalidad (50%)
  * 5% Entradas y validación
  * 5% Movimiento de Mario sobre el mundo
  * 5% Muestra toda la información de Mario (monedas, atacantes, objetivos, estrategia, activos, ganador)
  * 5% Integridad de la ejecución (programa no se cae, termina correctamente)
  * 10% Interacción con objetos (monedas, enemigos, hoyos)
  * 20% Manejo de las estrategias de ataque (aleatorio, +monedas, -monedas, atacantes)

* Código (40%)
  * 10% Clean code
  * 10% Clases y estructuras de datos
  * 15% Manejo de paso de mensajes (MPI)
  * 05% Documentación interna

* Documentación externa (10%)

* Creatividad en general (10 puntos extra sobre la nota del proyecto)

### Entrega

Este proyecto se podrá realizar en grupos de máximo 2 personas.

Las solución deberá ser subida a su repositorio *CI0117-2020-S2* creado para este curso en Github. Dentro de dicho repositorio se deberá crear un folder con el nombre *proyectos*. El nombre entre paréntesis cuadrados en el título del proyecto es el nombre a utilizar para el folder que contiene el proyecto.
Toda la documentación solicitada deberá estar en un archivo README.md en el folder raíz del proyecto.
El proyecto debe contener un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el nombre dado en el título. Cree un archivo .gitignore para evitar subir archivos ejecutables.

Únicamente uno de los integrantes del grupo requiere subir la solución.

### Material de apoyo:

* Estándar MPI - https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf
* Guía de Referencia rápida MPI - https://os.ecci.ucr.ac.cr/ci0117/slides/mpi-quick-ref.pdf
* Ejemplo de Gameplay Super Mario Bross 35 - https://www.youtube.com/watch?v=Z05l1bkDSbM&ab_channel=Jos%C3%A9Andr%C3%A9sMena.
* Imagen del primer mundo de Super Mario original - http://www.mariouniverse.com/wp-content/img/maps/nes/smb/1-1.png
