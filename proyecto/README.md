# CI0117 - Proyecto 1: Simulador de Batallas de Hilos [pthreadmon]

### Instrucciones generales

**Fecha de entrega:** Jueves 22 de Octubre 11:50pm.

### Introducción

El propósito de este proyecto es implementar un simulador de batallas entre hilos basándose en la dinámica de batallas PvP del juego [Pokémon GO](https://es.wikipedia.org/wiki/Pok%C3%A9mon_GO). En estas batallas dos jugadores se enfrentan utilizando 3 Pokémon cada uno, donde cada Pokémon tiene ataques y características específicas (ataques rápidos, ataques cargados, puntos de vida, entre otros). Un enfrentamiento entre dos Pokémon consiste en ambos atacando simultáneamente al otro hasta que uno de los dos se debilite (sus puntos de vida llegan a 0). El objetivo de cada jugador es lograr debilitar a los 3 Pokémon de su oponente antes de que el oponente debilite los suyos. Puede ver un ejemplo de cómo funcionan las batallas en [este video](https://youtu.be/oTUbkfzHm4Q).

Para efectos de este proyecto no se va a implementar el juego como tal, sino una simulación entre dos jugadores virtuales. De igual manera no todos los detalles del sistema de batallas estarán dentro del alcance de la simulación, únicamente las que se especifican en los requerimientos de las siguientes secciones.

### Requerimientos de datos

#### Pokémon
Un Pokémon tiene los siguientes atributos:
* *id*: Identificador de especie utilizado internamente por el programa
* *species name*: Nombre de la especie de Pokémon (Ej. lapras, registill, etc.)
* *HP*: Puntos de vida del Pokémon (Para este proyecto, todas las especies tendrán 1500 puntos de vida)
* *fast move*: Ataque rápido. Cada Pokémon tendrá únicamente un ataque rápido
* *charged move*: Ataque cargado. Cada Pokémon tendrá únicamente un ataque cargado
* *type*: Tipo de la especie de Pokémon (Ej. planta, fuego, normal, etc.). Cada Pokémon tendrá únicamente un tipo

La lista de Pokémon y sus atributos se limita a 50 especies diferentes definidas en [este archivo](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.c#L58).

#### Ataques
Cada ataque tiene los siguientes atributos:
* *id*: Identificador de ataque utilizado internamente por el programa
* *move name*: Nombre del ataque (Ej. BLIZZARD, BUBBLE, etc.)
* *cooldown*: Valor de reposo o enfriamiento en milisegundos. Si este ataque es realizado se debe esperar esta cantidad de milisegundos antes de realizar otro ataque.
* *energy*: Si es un ataque cargado, este valor contendrá la cantidad de energía necesaria a acumular antes de poder realizar el ataque.
* *energy gain*: Si es un ataque rápido, este valor contiene la cantidad de energía que se obtiene cada vez que se usa este ataque (necesaria para realizar un ataque cargado)
* *type*: Tipo del ataque (Ej. planta, fuego, normal, etc.). La lista de diferentes tipos es la misma para Ataques y para Pokémon

Para este proyecto se tomarán en cuenta 58 ataques diferentes definidos en [este archivo](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.c#L415).

#### Tipos
Cada tipo tiene los siguientes atributos:
* *id*: Identificador de tipo utilizado internamente por el programa
* *type name*: Nombre del tipo (Ej. planta, fuego, normal, etc.)

Existen 18 tipos diferentes, los cuales están definidos en [este archivo](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.c#L944). Adicionalmente, cada tipo tiene [propiedades de efectividad](https://niantic.helpshift.com/a/pokemon-go/?s=gyms-battle&f=type-effectiveness-in-battle&l=en&p=web), haciéndolo débil, resistente o inmune contra otros tipos. Esta información está mapeada en las matrices de [este archivo](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.h#L61).

### Requerimientos de la simulación

* Una simulación consistirá en una batalla entre dos jugadores virtuales, cada uno utilizando un equipo de 3 Pokémon.
* Cada jugador tendrá 3 Pokémon en un orden específico. Tanto los Pokémon a utilizar como el orden serán indicados por el usuario antes de iniciar la simulación. El programa no debe permitir que un jugador tenga dos Pokémon de la misma especie en su equipo.
* Durante la simulación, solamente podrá haber dos Pokémon, uno de cada jugador, peleando entre ellos en el campo de batalla (Pokémon activos). El resto de Pokémon estarán inactivos.
* Para un jugador, sus Pokémon se irán activando en el orden definido por el usuario. Un Pokémon activo debe continuar peleando hasta ser debilitado y no podrá regresar al campo de batalla, en ese caso entrará el siguiente Pokémon de acuerdo al orden.
* Cuando los 3 Pokémon de un jugador fueron debilitados, la simulación termina. En este caso se muestra cuál de los jugadores ganó la batalla y las siguientes estadísticas:
  * Duración total de la batalla
  * Tiempo que tardó cada Pokémon de cada jugador mientras estuvo activo
* Una vez terminada la simulación, el usuario puede cambiar los Pokémon a utilizar por cada jugador y empezar otra simulación.

#### Pokémon Activo
Cada Pokémon, mientras está activo, deberá realizar lo siguiente:
* Mientras sus puntos de vida no hayan llegado a 0, deberá realizar ataques rápidos continuamente a su oponente.
  * El daño realizado debe estar basado en el poder del ataque rápido y su efectividad contra el tipo del Pokémon siendo atacado. Dicho daño se decrementa de los puntos de vida del Pokémon oponente.
  * Cada vez que realiza un ataque rápido, el gane de energía debe irse acumulando para ese Pokémon.
  * Luego de realizar un ataque rápido, el Pokémon debe esperar el tiempo de enfriamiento respectivo (*cooldown*) antes de poder volver a atacar.
  * Si el oponente está realizando un ataque cargado, este Pokémon NO podrá realizar ningún ataque.
* Mientras sus puntos de vida no hayan llegado a 0 y se tenga la energía suficiente, deberá realizar el ataque cargado a su oponente.
  * El daño realizado debe estar basado en el poder del ataque cargado y su efectividad contra el tipo del Pokémon siendo atacado. Dicho daño se decrementa de los puntos de vida del Pokémon oponente.
  * Cada vez que realiza un ataque cargado, la energía de ese ataque se decrementa de la energía acumulada del Pokémon.
  * Luego de realizar un ataque cargado, el Pokémon debe esperar el tiempo de enfriamiento respectivo (*cooldown*) antes de poder volver a atacar.
  * Sólamente uno de los dos Pokémon activos puede realizar un ataque cargado a la vez.
* Cuando sus puntos de vida llegan a 0, el Pokémon activo debe terminar su interacción durante el resto de la simulación.

### Requerimientos de implementación
* El programa debe contener todas las validaciones necesarias, principalmente para los valores ingresados por el usuario, de forma que se mantenga la integridad de la ejecución y se cumpla con los requerimientos.
* El programa debe estar estructurado en diferentes folders y/o archivos .c con sus respectivos archivos de encabezado .h basándose en el principio de separación de responsabilides. Puede seguir una architectura [Modelo-Vista-Controlador (MVC)](https://si.ua.es/es/documentacion/asp-net-mvc-3/1-dia/modelo-vista-controlador-mvc.html#:~:text=Modelo%20Vista%20Controlador%20(MVC)%20es,control%20en%20tres%20componentes%20distintos.&text=La%20Vista%2C%20o%20interfaz%20de,los%20mecanismos%20interacci%C3%B3n%20con%20%C3%A9ste.) para organizar los archivos.
* Importe en su programa los archivos [mapper.h](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.h) y [mapper.c](https://github.com/jocan3/CI9117-2020-S2/blob/master/Enunciados/Proyectos/Proyecto_1/mapper.c) dados por el profesor. Estos archivos contienen toda la información referente a las especies de Pokémon, ataques y tipos requeridos para el proyecto. Dichos archivos no requieren modificación y puede hacer uso de los métodos definidos en el encabezado (Puede realizar modificaciones si lo considera necesario).
* El cálculo del daño de un ataque se puede realizar de la siguiente manera:

```
floor(power * effectiveness * bonus) + 1
```

Donde *power* es el valor del poder del ataque, *effectiveness* es el factor de efectividad basado en el tipo del movimiento y el tipo del Pokémon siendo atacado (1.6 si es muy efectivo, 0.625 si no es muy efectivo y 0.390625 si no lo afecta) y *bonus* va a ser una constante de 2.3.

* Cada Pokémon deberá ser representado mediante un hilo haciendo uso de la biblioteca de pthreads de C. Esto significa que durante cada simulación debe haber al menos 6 hilos simultáneamente (3 hilos por cada jugador virtual).
* Los hilos de los 6 Pokémon deberán ser creados al inicio de la simulación, incluyendo los que estarán inactivos. La batalla durante la simulación no debe comenzar hasta que todos los hilos hayan sido creados.
* Utilice cualquiera de los métodos de sincronización vistos en clase para proteger los accesos compartidos y coordinar la interacción entre los Pokémon (hilos). Su solución no debe permitir problemas de sincronización como *starvation* o *deadlock*.
* Asegúrese de no generar accesos inválidos ni fugas de memoria.

#### Interfaz gráfica
* Implemente una interfaz gráfica para su programa. Dicha interfaz debe permitir el ingreso de los valores por parte del usuario (Pokémon de cada jugador virtual) y un botón para iniciar la simulación.
* Durante la simulación, la interfaz debe mostrar lo que está ocurriendo durante la batalla: Los Pokémon activos, sus puntos de vida, la cantidad total de energía requerida y la acumulada y Pokémon restantes para cada jugador.
* Puede agregar un "sleep" fijo durante cada ataque, adicional al tiempo de enfriamiendo, y que la interfaz muestre quién está realizando un ataque (rápido o cargado) durante la simulación.
* Las estadísticas finales también deben ser mostradas en la interfaz al finalizar la ejecución de una simulación.
* La interfaz no requiere ser muy compleja, pero los estudiantes pueden explorar el hacer uso de imágenes para representar a los Pokémon (Pueden utilizar el folder de [sprites](https://github.com/jocan3/CI9117-2020-S2/tree/master/Enunciados/Proyectos/Proyecto_1/sprites) adjunto).
* Se recomienda utilizar la biblioteca [GTK+](https://developer.gnome.org/gtk3/stable/gtk-getting-started.html), pero queda a criterio del estudiante qué biblioteca utilizar así como el diseño de la interfaz. 

### Documentación

La documentación del proyecto debe contener las siguientes secciones:

* Manual de usuario: Incluir información sobre cómo compilar el código fuente y bibliotecas adicionales a instalar. Información sobre cómo utilizar el programa (entradas esperadas e interpretación de resultados).

* Detalles de la solución: Estructura del programa (folders, archivos y tipos definidos) y breve descripción de cada uno de los componentes. Puede agregar un diagrama de componentes para representar la interacción entre los elementos.

* Métodos de sincronización: Para cada uno de los métodos de sincronzación utilizados en su solución, explique brevemente su función dentro del programa. Si durante la implementación se presentó algún problema de *starvation* o *deadlock*, documéntelo en esta sección junto con la manera en cómo lo solucionó.

### Entrega

Este proyecto se podrá realizar en grupos de máximo 2 personas.

Las solución deberá ser subida a su repositorio *CI0117-2020-S2* creado para este curso en Github. Dentro de dicho repositorio se deberá crear un folder con el nombre *proyectos*. El nombre entre paréntesis cuadrados en el título del proyecto es el nombre a utilizar para el folder que contiene el proyecto.
Toda la documentación solicitada deberá estar en un archivo README.md en el folder raíz del proyecto.
El proyecto debe contener un archivo *Makefile* con los comandos necesarios para compilar el codigo fuente, de forma que el ejecutable tenga el nombre dado en el título. Cree un archivo .gitignore para evitar subir archivos ejecutables.

Únicamente uno de los integrantes del grupo requiere subir la solución.

### Material de apoyo:

* Ejemplo de batalla PvP de Pokémon Go  - https://youtu.be/oTUbkfzHm4Q
* GTK+ Tutorial - https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
