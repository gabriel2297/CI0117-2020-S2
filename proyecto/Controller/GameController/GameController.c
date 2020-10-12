#include <stdlib.h>
#include "GameController.h"

void endGame(player_t *player)
{
    liberarMemoriaJugador(player);
    free(player);
}

void startGame()
{
    // instanciar el jugador 1, ponerle nombre y mostrar su informacion
    player_t player1 = *(player_t *)malloc(sizeof(player_t));
    player1.playerId = 1;
    initializePlayer(&player1);
    showPlayerInformation(&player1);

    // instanciar el jugador 2, ponerle nombre y mostrar su informacion
    player_t player2 = *(player_t *)malloc(sizeof(player_t));
    player2.playerId = 2;
    initializePlayer(&player2);
    showPlayerInformation(&player2);

    // finalizar juego (liberar memoria, etc)
    endGame(&player1);
    endGame(&player2);
}