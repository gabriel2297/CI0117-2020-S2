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

    // crear los hilos que van a ser los pokemones y enviarles los datos del jugador
    pthread_t *player1Threads = malloc((size_t)(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t)));
    pthread_t *player2Threads = malloc((size_t)(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t)));

    // creo que esto se podria realizar de mejor manera ya que estamos pasando solo la informacion del pokemon y no todo el
    // jugador, pero veremos luego
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_create(player1Threads[i], NULL, placeholder, (void *)&player1->playerPokemons[i]);
        pthread_create(player2Threads[i], NULL, placeholder, (void *)&player1->playerPokemons[i]);
    }

    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_join(&player1[i], NULL);
        pthread_join(&player2[i], NULL);
    }

    // finalizar juego (liberar memoria, etc)
    destroyPlayer(player1);
    destroyPlayer(player2);
}

void *placeholder(void *args)
{
}