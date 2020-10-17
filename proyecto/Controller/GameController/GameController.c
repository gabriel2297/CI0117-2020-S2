#include <stdlib.h>
#include <pthread.h>
#include "GameController.h"

void destroyPlayer(player_t *player)
{
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        free(player->playerPokemons[i]->pokemon_info);
        free(player->playerPokemons[i]);
    }
    free(player->condition);
    free(player);
}

void startGame()
{
    // instanciar el jugador 1, ponerle nombre y mostrar su informacion
    player_t *player1 = (player_t *)malloc(sizeof(player_t));
    player1->condition = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * MAX_POKEMONS_PER_PLAYER);
    player1->playerId = 1;
    player1->pokemonTurn = 0;
    pthread_mutex_init(&player1->mutex, NULL);
    initializePlayer(player1);

    // instanciar el jugador 2, ponerle nombre y mostrar su informacion
    player_t *player2 = (player_t *)malloc(sizeof(player_t));
    player2->condition = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * MAX_POKEMONS_PER_PLAYER);
    player2->playerId = 2;
    player2->pokemonTurn = 0;
    pthread_mutex_init(&player2->mutex, NULL);    
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