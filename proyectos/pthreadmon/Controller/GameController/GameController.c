#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "GameController.h"
#include <string.h>
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

void startGame(int id_matrix[2][3])
{

    // instanciar el jugador 1, ponerle nombre y mostrar su informacion
    player_t *player1 = (player_t *)malloc(sizeof(player_t));
    player1->condition = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * MAX_POKEMONS_PER_PLAYER);
    player1->playerId = 1;
    player1->pokemonTurn = 0;
    strcpy(player1->nickname, "player1");
    initializePlayer(player1);
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i){
        set_pokemon_player(player1, i, id_matrix[0][i]);
    }

    // instanciar el jugador 2, ponerle nombre y mostrar su informacion
    player_t *player2 = (player_t *)malloc(sizeof(player_t));
    player2->condition = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * MAX_POKEMONS_PER_PLAYER);
    player2->playerId = 2;
    player2->pokemonTurn = 0;
    strcpy(player2->nickname, "player2");
    initializePlayer(player2);
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i){
        set_pokemon_player(player2, i, id_matrix[1][i]);
    }

    // iniciar batalla
    initBattle(player1, player2);

    // finalizar juego (liberar memoria, etc)
    destroyPlayer(player1);
    destroyPlayer(player2);
}