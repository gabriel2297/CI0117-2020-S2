# CI0117 - Proyecto 2: *Battle Royale* de Procesos [super_mario_mpi]

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

## Manual de usuario
### Compilando el programa:

El código fuente del programa se encuentra en GitHub.  Requerimientos para poder correr la solución:
1. Sistema Operativo Ubuntu 14.04 o superior.
2. Instalación del GNU Compiler (g++) y de  “make”. Para instalar, abrir el terminal del equipo y correr:
```
❯ sudo apt update
❯ sudo apt install build-essential
```
3. Para verificar que se haya instalado correctamente, al correr los siguientes comandos debemos obtener un resultado similar
```
❯ which g++
/usr/bin/g++
❯ which make
/usr/bin/make
```
4. Para poder correr el programa con MPI necesitaremos las bibliotecas externas que lo implementen, sea open-mpi o mpichl, podemos instalarlas con los comandos:
```
❯ sudo apt-get install -y mpich 
❯ sudo apt-get install -y openmpi-bin
```
5. Una vez instaladas las utilidades, proceder a moverse a la carpeta donde se encuentra descargado el proyecto y correr el comando “make”. Hecho esto, se puede correr el programa. Una ventana aparecera. 
```
❯ make
mpic++ -O0 -g -Wall main.cpp src/*.cpp -o super_mario_mpi
```
### Como utilizar el programa 

Una vez realizadas las instrucciones especificadas anteriormente se debe de correr el programa con el siguiente comando.
```
❯ mpiexec -n 5 --oversubscribe ./super_mario_mpi Mario "Strategy" 
```
Donde los argumentos Mario y Strategy corresponden al mario a monitorear durante la ejecución y a la estrategia del mismo. El Mario seleccionado debe debe de encontrarse en el intervalo [1, n - 1] donde n corresponde a la cantidad de procesos. Por otro lado, el argumento de Strategy define cual será la estrategia del mario seleccionado, a continuación se presentan las estrategias disponibles:

* R. aleatorio (*random*): Jugador A ataca aleatoriamente a un jugador activo B cada vez que elimina un enemigo.
* L. menos monedas (*less coins*): Jugador A ataca siempre al jugador activo que tenga menos monedas (si hay empate, se elige solamente 1).
* M. más monedas (*more coins*): Jugador A ataca siempre al jugador activo que tenga más monedas (si hay empate, se elige solamente 1).
* A. atacante (*attacker*): Jugador A ataca a uno de los jugadores atacantes cada vez que elimina un enemigo (si no hay atacantes, se elije aleatoriamente a un jugador activo B)

[Demostracion de ejecucion en terminal]
```
$mpiexec -n 20 --oversubscribe ./super_mario_mpi 15 L
Mario elegido: 15. Estrategia: less_coins. Total de procesos: 19
World pos. 0. Mario 15 is walking. Coins: 0 | attacking #0 | Attack strategy: less_coins. Total playing: 19
World pos. 1. Mario 15 is walking. Coins: 0 | attacking #1 | Attack strategy: less_coins. Total playing: 19
World pos. 2. Mario 15 is walking. Coins: 0 | attacking #1 | Attack strategy: less_coins. Total playing: 19
World pos. 3. Mario 15 is walking. Coins: 0 | attacking #1 | Attack strategy: less_coins. Total playing: 19
World pos. 3. Mario 15 didn't jump  and was killed by a Little Goomba. Coins: 0 | attacking #1 | Attack strategy: less_coins. Total playing: 19
 
```

Una vez terminada la ejecución se mostrará cual ha sido el Mario ganador.

## Detalles de la solucion
### Estructura del programa

La estructura del código se divide en el formato _src directory_ donde la distribución se realiza en tres carpetas principales dividiendo los ficheros de acorde al código fuente, heades y la documentación.

```
+--------------------------------
|main.cpp
|include/
|    +- enums.h
|    +- Game.h
|    +- Mapper.h
|    +- Mario.h
|    +- World.h
|    +- WorldElement.h
|    +- WorldElements/
|    |    + - Coins.h
|    |    + - Holes.h
|    |    + - KoopaTroopas.h
|    |    + - LittleGoombas.h
|src/
|    +- Enums.cpp
|    +- Game.cpp
|    +- Mapper.cpp
|    +- Mario.cpp
|    +- World.cpp	
+--------------------------------
```
- `main.cpp`: El archivo principal es el archivo `main.cpp`, el cual se encarga de inicializar el juego haciendo un llamado a la clase Game. 

- `include/enums.h`: en el header file `enums` se especifican las entidades principales utilizadas para la interacción de Mario en el mundo sean Elementos, Estrategias o Acciones.

- `include/Game.h`: en el header file `Game.h` se especifican las funciones necesarias para el funcionamiento correcto del juego, tales como la validacion de datos de entrada, obtencion de datos y otras tareas que los procesos deben de realizar para el correcto funcionamiento.

- `include/Mapper.h`: el header file `Mapper.h` funciona como una base de datos para la inicialización del mundo para insertar los elementos en las posiciones correspondientes.

- `include/Mario.h`: en el header file `Mario.h` se definen los atributos y métodos que tiene el objeto Mario, siendo este el que interactua con los elementos del mundos. 

- `include/World.h`: en el header file `World.h` se encuentran los métodos y atributos necesarios para la inicialización del mundo.

- `include/WorldElements.h`: en el header file `WorldElements.h` se define la clase abstracta de las cuales heredaran los elementos con los cuales Mario puede interactuar en el mundo.

- `include/WorldElements/Coins.h`: en el header file `Coins.h` se encuentra la definición e implementación de la clase derivada de WorldElements, aqui se especifican cual es el comportamiento y acciones que puede realizar Mario con las monedas en el mundo.

- `include/WorldElements/Holes.h`: en el header file `Holes.h` se encuentra la definición e implementación de la clase derivada de WorldElements, aqui se especifican cual es el comportamiento y acciones que puede realizar Mario con los agujeros en el mundo.

- `include/WorldElements/KoopaTroopas.h`: en el header file `KoopaTroopas.h` se encuentra la definición e implementación de la clase derivada de WorldElements, aqui se especifican cual es el comportamiento y acciones que puede realizar Mario con los Koopa Troopas en el mundo.

- `include/WorldElements/LittleGoombas.h`: en el header file `LittleGoombas.h` se encuentra la definición e implementación de la clase derivada de WorldElements, aqui se especifican cual es el comportamiento y acciones que puede realizar Mario con los Little Goombas en el mundo.

- `src/Enums.cpp`: en el source file `Enums.cpp` se encuentra información en enums con las cuales se puede facilitar la comunicación entre Mario con el mundo, similarmente para que dicha información sea facilmenta mostrada durante la ejecución del juego.

- `src/Game.cpp`: en el source file `Game.cpp` se encuentra gran parte de la implementación lógica del juego, igualmente acá se lleva a cabo la comunicación entre procesos mediante MPI.

- `src/Mapper.cpp`: en el source file `Mapper.cpp` se encuentra la implementación necesaria para inicializar cada instancia de un mundo, colocando los diferentes elementos en las posiciones correspondientes.

- `src/Mario.cpp`: en el source file `Mario.cpp` se encuentra la implementación del objeto Mario, el cual se encarga de interactuar con los diferentes elementos del mundo. De manera que cada proceso tiene una instancia a dicho objeto con los datos necesarios.

- `src/World.cpp`: en el source file `World.cpp` se encuentra la implementación lógica de los métodos necesarios para que Mario sea capaz de recorrer el mundo e interactuar con el.


### MPI

A continuación se presentan las funciones estándar de MPI utilizadas para la solución y como estas funcionan en el programa

```
❯ MPI_Allgather()
```
Hace un gather de datos a un buffer de manera que todos los procesos tiene los datos agrupados en un arreglo. 
En el programa es utilizado para enviar a un arreglo si el mario del proceso se encuentra vivo o no, de manera que todos los procesos pueden saber cual o cuales Marios se encuentran muertos.

```
MPI_Allgather(&this->mario_is_alive, 1, MPI_INT, processes_alive, 1, MPI_INT, MPI_COMM_WORLD);
```
A partir de los datos almacenados en el buffer se puede determinar cual es el Mario ganador o si el Mario seleccionado por el usuario se encuentra activo o no.

```
❯ MPI_Barrier()
```
Realiza un bloqueo parcial hasta que todos los procesos hayan llegado a dicha función.
En el programa es utilizado principalmente cuando el proceso 0 debe de realizar alguna validación de datos, o bien llamar a la entrada estándar de C++
```
mario->setPickedMario(picked_mario);
MPI_Barrier(MPI_COMM_WORLD);
```
Con esta función se impide que cuando el proceso 0 realiza alguna acción necesaria para el correcto funcionamiento del flujo de datos lo demás procesos sigan realizando las demás acciones.

```
❯ MPI_Bcast()
```
Permite enviar información desde un proceso raiz hacia los demás procesos.
En el programa es utilizado cuando es necesario enviar los valores de ciertos datos en concreto necesarios para la ejecución. Por ejemplo, decirle a los demás procesos cual es el Mario que ha sido seleccionado por el usuario, o enviar un buffer de monedas.

```
MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);
```
Con esta función se le envia a los demás procesos cual Mario ha sido seleccionado por el usuario.


```
❯ MPI_Gather()
```
Distribuye los valores locales de todos los procesos hacia el proceso raiz
En el programa es utilizado para enviar la estrategia escogida por los procesos al proceso 0.

```
MPI_Gather(&this->picked_strategy, 1, MPI_INT, strategy_per_process, 1, MPI_INT, 0, MPI_COMM_WORLD);
```

```
❯ MPI_Send()
```
Envia datos de un proceso hacia el proceso destino
En el programa es utilizado por el proceso cero para enviarle a los demás procesos a cual proceso deben de atacar.

```
MPI_Send(&attacking_processes[h], 1, MPI_INT, h, 123, MPI_COMM_WORLD);
```

```
❯ MPI_Recv()
```
Recibe datos del proceso especificado
En el programa es utilizado por los procesos jugadores para recibir el id del mario a atacar

```
MPI_Recv(&chosen_enemy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
```

Estas funciones de MPI explicadas anteriormente fueron fundamentales para asegurar el debido envio y recibo de mensajes entre procesos, de manera que sea posible realizar una comunicación eficaz y que la ejecución del programa se cumpla correctamente.

