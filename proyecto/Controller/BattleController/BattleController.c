#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthread_barrier.h"
#include "BattleController.h"

typedef struct
{
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    size_t playerTurn;
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

    // esperar a que lleguen todos los hilos
    pthread_barrier_wait(&shared_data->barrier);

    // obtener el mutex local para ver si es el turno de este pokemon, sino dormir y esperar
    pthread_mutex_lock(&player->mutex);
    if (thread_num != player->pokemonTurn)
    {
        pthread_cond_wait(&player->condition[thread_num], &player->mutex);
    }
    pthread_mutex_unlock(&player->mutex);
    printf("Player[%zu] - Thread[%zu] - Pokemon[%s] jugando\n", player->playerId, thread_num, pokemon->pokemon_info->speciesName);
    pokemon->start_time = clock();
    while (1)
    {
        // obtener el mutex global y local para revisar si es nuestro turno de atacar y si tenemos suficiente vida para hacerlo
        pthread_mutex_lock(&shared_data->mutex);
        if (player->playerId == shared_data->playerTurn && pokemon->hp > 0)
        {
            pthread_mutex_lock(&player->mutex);
            if (pokemon->hp <= 0)
            {
                // no tengo suficiente vida, salir
                pthread_mutex_unlock(&player->mutex);
                break;
            }
            printf("Player[%zu] - Thread[%zu] - Pokemon[%s] atacando\n", player->playerId, thread_num, pokemon->pokemon_info->speciesName);
            pthread_mutex_lock(&opponent->mutex);
            opponent->playerPokemons[opponent->pokemonTurn]->hp = opponent->playerPokemons[opponent->pokemonTurn]->hp - 500;
            shared_data->playerTurn = opponent->playerId;
            pthread_mutex_unlock(&opponent->mutex);
            pthread_mutex_unlock(&player->mutex);
        }
        pthread_mutex_unlock(&shared_data->mutex);
    }

    // pokemon murio, decirle al siguiente pokemon que se despierte o si somos el ultimo entonces salir
    pthread_mutex_lock(&player->mutex);
    printf("Player[%zu] - Thread[%zu] - Pokemon[%s] murio\n", player->playerId, thread_num, pokemon->pokemon_info->speciesName);
    ++player->pokemonTurn;
    if (!player->pokemonTurn >= MAX_POKEMONS_PER_PLAYER)
    {
        pthread_cond_signal(&player->condition[player->pokemonTurn]);
    }
    pthread_mutex_unlock(&player->mutex);
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
    pthread_mutex_init(&shared_data->mutex, NULL);
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
    free(player1_data);
    free(player2_data);
    free(shared_data);
    free(player1_threads);
    free(player2_threads);
}