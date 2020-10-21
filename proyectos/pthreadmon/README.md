# CI0117 - Proyecto 1: Simulador de Batallas de Hilos [pthreadmon]

## Estudiantes:
- Gabriel Umaña Frías (C09913)
- Emmanuel Zúñiga Chaves (B98729)

## Manual de usuario
### Compilando el programa:

El código fuente del programa se encuentra en GitHub.  Requerimientos para poder correr la solución:
1. Sistema Operativo Ubuntu 14.04 o superior.
2. Instalación del GNU Compiler (gcc) y de  “make”. Para instalar, abrir el terminal del equipo y correr:
```
❯ sudo apt update
❯ sudo apt install build-essential
```
3. Para verificar que se haya instalado correctamente, al correr los siguientes comandos debemos obtener un resultado similar
```
❯ which gcc
/usr/bin/gcc
❯ which make
/usr/bin/make
```
4. Para poder correr el programa necesitaremos las bibliotecas de GTK, en su versión 3.0+, podemos instalarlas con los comandos:
```
❯ sudo apt-get install libgtk-3-dev 
❯ sudo apt install pkg-config 
❯ sudo apt-get install glade
```
5. Una vez instaladas las utilidades, proceder a moverse a la carpeta donde se encuentra descargado el proyecto y correr el comando “make”. Hecho esto, se puede correr el programa. Una ventana aparecera. 
```
❯ make
gcc `pkg-config --cflags gtk+-3.0` -O0 -g -o pthreadmon main.c Model/mapper.c Controller/GameController/GameController.c Controller/PlayerController/PlayerController.c Controller/BattleController/BattleController.c Controller/PokemonController/PokemonController.c -pthread -lm `pkg-config --libs gtk+-3.0`
❯ ./pthreadmon
```
### Como utilizar el programa 

Una vez que se corrieron los comandos anteriores se mostrará una ventana similar a la que se muestra en la imagen de abajo. Para iniciar el juego es necesario dar click en “Start!”. 

A continuación el usuario será presentado con una pantalla en donde deberá elegir los pokemones de cada jugador, hemos hecho esta seleccion simple al usar dropdowns. Una vez seleccionados todos los pokemones el usuario puede dar click a "Start Battle!", lo que procedera a cargar los pokemones de los jugadores y la batalla iniciara, el usuario podra ver de manera interactiva como los pokemons van atacandose, cual ataca, la vida restante, la energia acumulada y la energia necesaria para realizar un ataque cargado. 

Al finalizar la partida se muestran las estadisticas del juego. Entre ellas se muestra: 
1. La duracion total de la partida, en segundos.
2. La duracion de cada pokemon, de cada jugador, en segundos. 

En esta misma ventana se muestra un boton para reiniciar la batalla, al darle click los usuarios seran llevados a la interfaz anterior para seleccionar los pokemones y la aplicacion empezara desde 0. 

### Estructura del programa

El programa utiliza un modelo MVC, lo cual divide las diferentes funciones en una vista (encargada de interactuar con el usuario), un controlador (encargada de controlar lo que hace el usuario) y un modelo (encargado de obtener datos, etc). A continuacion se muestra la division de directorios que se ha hecho y lo que cada uno contiene. 

```
+--------------------------------
|main.c
|Model/
|    |-mapper.c
|    +-mapper.h
|View/
|    |-Images/
|    |   |-icon.png
|    |   +-Pokemon_logo.png
|    |-sprites/
|    |   |-abomasnow.png
|    |   +-alomomola.png
|    |   +-.
|    |   +-.
|    |   +-.
|    |-Interface.glade
|    +-interface.h
|Controller/
|    |-BattleController/
|    |   |-BattleController.c
|    |   +-BattleController.h
|    |-GameController/
|    |   |-GameController.c
|    |   +-ameController.h
|    |-PlayerController/
|    |   |-PlayerController.c
|    |   +-PlayerController.h
|    +-PokemonController/
|        |-PokemonController.c
|        +-PokemonController.h
+--------------------------------
```
- `main.c`: El archivo principal es el archivo `main.c`, el cual se encarga de levantar la interface y empezar la interaccion con los usuarios. 

- `Model/mapper.c`: el archivo mapper.c sirve como base de datos. De aqui el controllador `PokemonController.c` obtiene la informacion de los pokemones, los ataques de cada pokemon y los tipos. 

- `View/Images/`: esta carpeta es utilizada para guardar las imagenes que el juego carga para la interfaz grafica.

- `View/sprites/`: en el folder de sprites guardamos las diferentes imagenes que utilizamos para mostrar cual pokemon se encuentra en batalla. 

- `View/Interface.glade`: el `Interface.glade` genera el codigo css que el GTK builder necesita para poder hacer "render" de todos los widgets y ventanas utilizados en la interfaz grafica de la aplicacion. 

- `View/interface.h`: en el header file `interface.h` definimos las funciones que seran exportadas para que otros archivos puedan llamarlas.

- `Controller/BattleController/*`: en el archivo `BattleController.c` realizamos toda la logica de las batallas. Es aqui donde el archivo `GameController.c` realiza la inicializacion de la batalla y donde cada hilo (pokemon) se crea para pelear. Este mismo archivo contiene la funcion `fight`, que es donde se realiza la sincronizacion entre hilos para llevar acabo la pelea. Mas adelante se explicaran las primitivas de sincronizacion que se han puesto en practica. 

- `Controller/GameController/*`: dentro de este folder podemos encontrar el archivo `.c` que "orquesta" el juego. Desde la instanciacion de los jugadores, la asignacion de pokemones a los mismos, como dar inicio a la batalla y liberar la memoria utilizada durante el programa. 

- `Controller/PlayerController/*`: los archivos `PlayerController.c` y `PlayerController.h` contienen el codigo necesario para que un jugador sea creado. En estos dos archivos definimos los metodos para crear un jugador, los datos necesarios para instanciar un jugador y realizamos la asignacion de pokemones al jugador, en base a lo que el usuario eligio en la interfaz grafica.

- `Controller/PokemonController/*`: esta carpeta es la que interactua mas con el modelo, dado que es donde los pokemones son instanciados para cada jugador y por cada pokemon necesitaremos obtener los datos del pokemon, los ataques de dicho pokemon y el tipo de ataque. En este mismo `PokemonController.c` realizamos el calculo de la efectividad de los ataques de un pokemon a otro, asi como tambien el daño que dicho ataque cargado o ataque rapido genera en el otro pokemon. 

### Metodos de sincronizacion

A continuacion se muestran los diferentes metodos de sincronizacion que hemos utilizado en nuestro programa. Cabe destacar que no nos encontramos con problemas de deadlocks ni starvation, por la manera en que realizamos la arquitectura a la hora de usar estas primitivas.

Todas las primitivas de sincronizacion se encuentran en el archivo `BattleController.c` que, como mencionado anteriormente, es donde tenemos la logica de la batalla. En dicha carpeta definimos un `shared_data_t`, una estructura de C que es utilizada para compartir datos entre hilos. Mediante esta estructura logramos que los hilos usen el mismo `mutex` y el mismo `barrier`, dos de las tres primitivas de sincronizacion que utilizamos:

```
typedef struct
{
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    size_t playerTurn;
    size_t isLast;
} shared_data_t;
```

### Secuencia de la batalla: 
1. Una vez empieza la batalla (el usuario ha elegido los pokemones para cada jugador), se llama a la funcion initBattle, que recibe como parametro un puntero a cada jugador, que a su vez contienen un puntero a sus pokemons: 

```
void initBattle(player_t *player1, player_t *player2)
{
    ....
}
```

2. Como se aprecia en el codigo de abajo, utilizamos un `pthread_mutexattr_t` con el tipo `PTHREAD_MUTEX_RECURSIVE` para lograr que un hilo pueda apropiarse de un `mutex` mas de una vez. Sin este atributo los hilos solo pueden hacer `lock` del `mutex` al iniciar el juego por lo que falla al intentarlo luego de esta. En esta funcion tambien realizamos la inicializacion del mutex, junto con su atibuto, y la inicializacion de la barrera, en donde un total de 6 hilos deberan llegar para poder proceder. 

```
void initBattle(player_t *player1, player_t *player2)
{
 // crear los hilos de los jugadores
    pthread_t *player1_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));
    pthread_t *player2_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));

    // crear los datos compartidos por los hilos
    shared_data_t *shared_data = (shared_data_t *)malloc(sizeof(shared_data_t));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&shared_data->mutex, &attr);
    pthread_barrier_init(&shared_data->barrier, NULL, (MAX_POKEMONS_PER_PLAYER * 2));
}
```

3. En el archivo `PlayerController.h` hemos definido los datos que cada jugador tendra. Cada jugador tiene un arreglo de variables de condiciones la que nos permite dormir o notificar a cada hilo de cuando es su turno de atacar o de realizar cierta accion:
```
typedef struct
{
    int playerId;
    size_t pokemonTurn;
    char nickname[MAX_CHARS_PLAYER_NICKNAME];
    pokemon_t *playerPokemons[MAX_POKEMONS_PER_PLAYER];
    pthread_cond_t *condition;
} player_t;
```

4. La informacion anterior la inicializamos justo antes de la creacion de cada hilo (o pokemon), y le pasamos la informacion recien creada al hilo, por lo que cada hilo tendra su propia variable de condicion:

```
// inicializar los hilos
for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
{
    pthread_cond_init(&player1_data->player->condition[i], NULL);
    pthread_create(&player1_threads[i], NULL, fight, (void *)&player1_data[i]);

    pthread_cond_init(&player2_data->player->condition[i], NULL);
    pthread_create(&player2_threads[i], NULL, fight, (void *)&player2_data[i]);
}
```

5. Cada hilo llamara a la funcion `fight`, que se muestra a continuacion. Al empezar a correr, los hilos primero esperaran en la barrera hasta que los 6 de ellos lleguen. Una vez que todos se encuentran aqui, proceden a revisar si es el turno de ellos. Si lo es, tomaran el mutex y empezaran a batallar. De no serlo, los hilos esperaran en su variable de condicion, soltando el mutex y seguidamente, durmiendo:

```
void *fight(void *args)
{
    pthread_barrier_wait(&shared_data->barrier);
    pthread_mutex_lock(&shared_data->mutex);
    if (thread_num != player->pokemonTurn)
    {
        pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
    }
}
```
6. Los hilos que si hayan continuado ejecutandose dado que es el turno de ellos, entraran en un loop infinito. Primero revisaran si es el turno de ellos para atacar, de no ser asi se pondran a dormir mediante el `pthread_cond_wait` y liberaran el mutex para que el pokemon que si debe atacar lo haga. Este a continuacion revisara su vida y atacara mediante un ataque rapido o un ataque cargado, dependiendo de la cantidad de energia que tenga. Una vez realizado el ataque, el hilo indicara al siguiente pokemon que puede proceder a atacar y se pondra a dormir, liberando de nuevo el mutex para que el otro hilo lo pueda recuperar. Los turnos pasaran y si la vida del pokemon se disminuye a 0 o es el ultimo pokemon vivo, procederan a liberar el mutex y salir del loop. 

```
while (1)
{
    if (player->playerId == shared_data->playerTurn)
    {
        if (pokemon->hp <= 0)
        {
            pthread_mutex_unlock(&shared_data->mutex);
            break;
        }
        else if (shared_data->isLast)
        {
            pthread_mutex_unlock(&shared_data->mutex);
            break;
        }

        if(energyCharged >= chargedMove->energy)
        {
            pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
        }
        else
        {
            pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
        }
        pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
    }
    else 
    {
        pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
    }
}
```

7. Fuera del loop, los pokemones revisaran si quedan aun pokemons por batallar. De ser verdadero le diran al compañero que puede ingresar a batallar, y soltaran el mutex. De ser los ultimos en la batalla, le indicaran al ultimo hilo del contrincante que han ganado, para asi finalizar la batalla. 

```
if (player->pokemonTurn < (size_t)MAX_POKEMONS_PER_PLAYER)
{
    pthread_cond_signal(&player->condition[player->pokemonTurn]);
}
else if (player->pokemonTurn == (size_t)MAX_POKEMONS_PER_PLAYER && opponent->pokemonTurn < (size_t)MAX_POKEMONS_PER_PLAYER)
{
    shared_data->playerTurn = opponent->playerId;
    shared_data->isLast = 1;
    pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
}
```