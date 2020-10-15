#include <stdlib.h>
#include "GameController.h"

void destroyPlayer(player_t *player)
{
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        free(player->playerPokemons[i]->pokemon_info);
        free(player->playerPokemons[i]);
    }
    free(player);
}

void startGame()
{
    // instanciar el jugador 1, ponerle nombre y mostrar su informacion
    player_t *player1 = (player_t *)malloc(sizeof(player_t));
    player1->playerId = 1;
    initializePlayer(player1);

    // instanciar el jugador 2, ponerle nombre y mostrar su informacion
    player_t *player2 = (player_t *)malloc(sizeof(player_t));
    player2->playerId = 2;
    initializePlayer(player2);

    // mostrar la informacion de los jugadores
    showPlayerInformation(player1);
    showPlayerInformation(player2);

    // iniciar batalla
    initBattle(player1, player2);

    // finalizar juego (liberar memoria, etc)
    destroyPlayer(player1);
    destroyPlayer(player2);
}