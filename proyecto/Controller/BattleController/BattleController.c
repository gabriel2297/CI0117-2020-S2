#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "pthread_barrier.h"
#include "BattleController.h"

typedef struct
{
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    size_t playerTurn;
    size_t isLast;
} shared_data_t;

typedef struct
{
    size_t thread_num;
    shared_data_t *shared_data;
    player_t *player;
    player_t *opponent;
} thread_data_t;

void *fight(void *args)
{
    // obtener los datos que nos enviaron al crear el hilo
    thread_data_t *local_data = (thread_data_t *)args;
    shared_data_t *shared_data = local_data->shared_data;
    player_t *player = local_data->player;
    player_t *opponent = local_data->opponent;
    size_t thread_num = local_data->thread_num;
    pokemon_t *pokemon = player->playerPokemons[thread_num];

    pthread_barrier_wait(&shared_data->barrier);

    pthread_mutex_lock(&shared_data->mutex);
    if (thread_num != player->pokemonTurn)
    {
        pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
    }

    pokemon->start_time = clock();

    while (1)
    {
        sleep(3);
        if (player->playerId == shared_data->playerTurn)
        {
            if (pokemon->hp <= 0 || shared_data->isLast)
            {
                pthread_mutex_unlock(&shared_data->mutex);
                break;
            }
            printf("%s:\n\t> %s ataca a %s!\n", player->nickname, pokemon->pokemon_info->speciesName, opponent->playerPokemons[opponent->pokemonTurn]->pokemon_info->speciesName);
            opponent->playerPokemons[opponent->pokemonTurn]->hp = opponent->playerPokemons[opponent->pokemonTurn]->hp - 500;
            shared_data->playerTurn = opponent->playerId;
            printf("\t> Ataque efectivo! Redujo la vida de %s a %zu\n", opponent->playerPokemons[opponent->pokemonTurn]->pokemon_info->speciesName, opponent->playerPokemons[opponent->pokemonTurn]->hp);
            pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
            pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
        }
        else 
        {
            pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
        }
    }

    ++player->pokemonTurn;
    if (player->pokemonTurn < (size_t)MAX_POKEMONS_PER_PLAYER)
    {
        printf("%s:\n\t> %s yo te elijo!\n", player->nickname, player->playerPokemons[player->pokemonTurn]->pokemon_info->speciesName);
        pthread_cond_signal(&player->condition[player->pokemonTurn]);
    }
    else if (player->pokemonTurn == (size_t)MAX_POKEMONS_PER_PLAYER && opponent->pokemonTurn < (size_t)MAX_POKEMONS_PER_PLAYER)
    {
        shared_data->playerTurn = opponent->playerId;
        shared_data->isLast = 1;
        pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
    }
    pokemon->end_time = clock();
    return NULL;
}

void initBattle(player_t *player1, player_t *player2)
{
    // crear los hilos de los jugadores
    pthread_t *player1_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));
    pthread_t *player2_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));

    // crear los datos compartidos por los hilos
    shared_data_t *shared_data = (shared_data_t *)malloc(sizeof(shared_data_t));
    shared_data->playerTurn = 1;
    shared_data->isLast = 0;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&shared_data->mutex, &attr);
    pthread_barrier_init(&shared_data->barrier, NULL, (MAX_POKEMONS_PER_PLAYER * 2));

    // crear los datos necesarios por hilo
    thread_data_t *player1_data = (thread_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(thread_data_t));
    thread_data_t *player2_data = (thread_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(thread_data_t));

    // inicializar los hilos
    clock_t start_time = clock();
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        player1_data[i].thread_num = i;
        player1_data[i].shared_data = shared_data;
        player1_data[i].player = player1;
        player1_data[i].opponent = player2;
        pthread_cond_init(&player1_data->player->condition[i], NULL);
        pthread_create(&player1_threads[i], NULL, fight, (void *)&player1_data[i]);

        player2_data[i].thread_num = i;
        player2_data[i].shared_data = shared_data;
        player2_data[i].player = player2;
        player2_data[i].opponent = player1;
        pthread_cond_init(&player2_data->player->condition[i], NULL);
        pthread_create(&player2_threads[i], NULL, fight, (void *)&player2_data[i]);
    }

    //TODO: hay un bug en pthread_join que cambia la direccion de memoria de playerX->playerPokemons[i]->pokemon_info lo que causa
    // que el codigo de las estadisticas tire segmentation fault
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_join(player1_threads[i], NULL);
        pthread_join(player2_threads[i], NULL);
    }

    // parar el tiempo y calcular el tiempo que tardo la batalla, aprovechar para destruir las variables de condicion
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Duracion de la batalla: %f segundos\n", execution_time);
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        printf("\t- Pokemon %s del jugador %s duro %ld en la batalla\n", player1->playerPokemons[i]->pokemon_info->speciesName, player1->nickname, ((player1->playerPokemons[i]->end_time - player1->playerPokemons[i]->end_time) / CLOCKS_PER_SEC));
        pthread_cond_destroy(&player1->condition[i]);
        printf("\t- Pokemon %s del jugador %s duro %ld en la batalla\n", player2->playerPokemons[i]->pokemon_info->speciesName, player2->nickname, ((player2->playerPokemons[i]->end_time - player2->playerPokemons[i]->end_time) / CLOCKS_PER_SEC));
        pthread_cond_destroy(&player2->condition[i]);
    }

    // liberar datos
    pthread_mutex_destroy(&shared_data->mutex);
    pthread_barrier_destroy(&shared_data->barrier);
    pthread_mutexattr_destroy(&attr);
    free(player1_data);
    free(player2_data);
    free(shared_data);
    free(player1_threads);
    free(player2_threads);
}