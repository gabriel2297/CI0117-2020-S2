#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Controller/GameController/GameController.h"

int main(int argc, char *argv[])
{
    initialize_data();
    printf("\e[1;1H\e[2J");

    // inicia el juego, vamos a preguntarle al usuario si quiere jugar o si quiere salir
    char response[2];
    printf(" ####    ###   #   #  #####  #   #   ###   #   #          ###    ###   \n");
    printf(" #   #  #   #  #  #   #      #   #  #   #  #   #         #   #  #   #  \n");
    printf(" #   #  #   #  # #    #      ## ##  #   #  ##  #         #      #   #  \n");
    printf(" ####   #   #  ##     ####   # # #  #   #  # # #         #      #   #  \n");
    printf(" #      #   #  # #    #      #   #  #   #  #  ##         #  ##  #   #  \n");
    printf(" #      #   #  #  #   #      #   #  #   #  #   #         #   #  #   #  \n");
    printf(" #       ###   #   #  #####  #   #   ###   #   #          ###    ###   \n\n\n");
    printf("  ###    ###   #   #  #   #  #        #    #####   ###   ####  \n");
    printf(" #   #    #    #   #  #   #  #       # #     #    #   #  #   # \n");
    printf(" #        #    ## ##  #   #  #      #   #    #    #   #  #   # \n");
    printf("  ###     #    # # #  #   #  #      #   #    #    #   #  ####  \n");
    printf("     #    #    #   #  #   #  #      #####    #    #   #  # #   \n");
    printf(" #   #    #    #   #  #   #  #      #   #    #    #   #  #  #  \n");
    printf("  ###    ###   #   #   ###   #####  #   #    #     ###   #   # \n\n\n");
    printf("Bienvenido a la simulacion de Pokemon! Desea jugar (y) o salir (n)? (y/n): ");
    do
    {
        // "1s" es porque 1 = el primer char, el char 2 va a ser \0, que significa "EOF"
        scanf("%1s", response);
        if (strcmp("y", &response[0]) == 0)
        {
            printf("\e[1;1H\e[2J");
            printf("Eligio \"%c\", continuando\n", response[0]);
            startGame();
            printf("\n\nPartida finalizada! Desea jugar de nuevo (y) o salir (n)? (y/n): ");
        }
        else if (strcmp("n", &response[0]) == 0)
        {
            printf("\e[1;1H\e[2J");
            printf("Eligio \"%c\". Gracias por jugar.. Adiós!\n", response[0]);
            exit(0);
        }
        else
        {
            printf("\"%c\" no es una opción válida, inténtelo de nuevo. Desea jugar (y) o salir (n)? (y/n): ", response[0]);
        }
        // hacer flush al buffer de stdin ya que si un usuario pone mas de un char, se van a imprimir todos los del buffer
        fflush(stdin);
    } while (1);
    return 0;
}
