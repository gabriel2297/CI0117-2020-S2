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
gcc `pkg-config --cflags gtk+-3.0` -o pthreadmon interface.c `pkg-config --libs gtk+-3.0`
❯ ./pthreadmon
```
#### Como utilizar el programa 

Una vez que se corrieron los comandos anteriores se mostrará una ventana similar a la que se muestra en la imagen de abajo. Para iniciar el juego es necesario dar click en “Start!”. 

A continuación el usuario será presentado con una pantalla en donde deberá elegir los pokemones de cada jugador, hemos hecho esta seleccion simple al usar dropdowns. Una vez seleccionados todos los pokemones el usuario puede dar click a "Start Battle!", lo que procedera a cargar los pokemones de los jugadores y la batalla iniciara, el usuario podra ver de manera interactiva como los pokemons van atacandose, cual ataca, la vida restante, la energia acumulada y la energia necesaria para realizar un ataque cargado. 

Al finalizar la partida se muestran las estadisticas del juego. Entre ellas se muestra: 
1. La duracion total de la partida, en segundos.
2. La duracion de cada pokemon, de cada jugador, en segundos. 

En esta misma ventana se muestra un boton para reiniciar la batalla, al darle click los usuarios seran llevados a la interfaz anterior para seleccionar los pokemones y la aplicacion empezara desde 0. 

### Estructura del programa

El programa utiliza un modelo MVC, lo cual divide las diferentes funciones en una vista (encargada de interactuar con el usuario), un controlador (encargada de controlar lo que hace el usuario) y un modelo (encargado de obtener datos, etc). A continuacion se muestra la division de directorios que se ha hecho y lo que cada uno contiene. 

```
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
```
`main.c`: El archivo principal es el archivo `main.c`, el cual se encarga de levantar la interface y empezar la interaccion con los usuarios. 
`Model/mapper.c`: el archivo mapper.c 

