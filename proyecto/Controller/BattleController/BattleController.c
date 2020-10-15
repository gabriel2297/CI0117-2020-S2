#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "BattleController.h"

typedef struct
{
    size_t player1_turn;
    size_t player2_turn;
    size_t isStartTimeSet;
    clock_t start_time;
    clock_t end_time;
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    pthread_cond_t condition;
} battle_data_t;

typedef struct
{
    size_t thread_num;
    battle_data_t *battle_data;
    pokemon_t *pokemon;
    player_t *player;
    double fighting_time;
} player_data_t;

void *fight(void *args)
{
    // obtener los datos que nos enviaron al crear el hilo
    player_data_t *local_data = (player_data_t *)args;
    battle_data_t *shared_data = local_data->battle_data;

    // bloquear el mutex general y empezar el contador
    pthread_mutex_lock(&shared_data->mutex);
    if (!shared_data->isStartTimeSet)
    {
        shared_data->start_time = clock();
        shared_data->isStartTimeSet = 1;
    }
    pthread_mutex_unlock(&shared_data->mutex);

    // ahora esperar en la barrera a que lleguen todos los hilos para asi empezar la batalla
    printf("thread[%zu] - jugador %s esperando en la barrera...\n", local_data->thread_num, local_data->player->nickname);
    pthread_barrier_wait(&shared_data->barrier);
    printf("thread[%zu] - jugador %s uso %s\n", local_data->thread_num, local_data->player->nickname, local_data->pokemon->pokemon_info->speciesName);

    // Mientras la vida del pokemon sea mayor a 0
    // while (local_data->pokemon->hp > 0)
    // {
    //     pthread_mutex_lock(&shared_data->mutex);
    //     // voy a revisar si es mi turno. Los pokemones se crean de manera secuencial, a como se ingresaron en el arreglo
    //     // (como los especifico el usuario), entonces el numero de hilo debe ser igual al numero del pokemon que esta compitieno.
    //     if (local_data->thread_num == shared_data->player1_turn)
    //     {
    //         // no es mi turno, dormir
    //         pthread_cond_wait(&shared_data->condition, &shared_data->mutex);
    //     }
    // }
    // // pokemon murio, aumentar el contador y soltar el mutex
    // pthread_mutex_unlock(&shared_data->mutex);

    return NULL;
}

void initBattle(player_t *player1, player_t *player2)
{
    // crear los hilos de los jugadores
    pthread_t *player1_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));
    pthread_t *player2_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));

    // crear los datos compartidos por los hilos
    battle_data_t *shared_battle_data = (battle_data_t *)malloc((MAX_POKEMONS_PER_PLAYER * 2) * sizeof(battle_data_t));
    shared_battle_data->player1_turn = 0;
    shared_battle_data->player2_turn = 0;
    shared_battle_data->isStartTimeSet = 0;

    // inicializar los metodos de sincronizacion
    pthread_mutex_init(&shared_battle_data->mutex, NULL);
    pthread_barrier_init(&shared_battle_data->barrier, NULL, (MAX_POKEMONS_PER_PLAYER * 2));
    pthread_cond_init(&shared_battle_data->condition, NULL);

    // crear los datos necesarios por hilo
    player_data_t *player1_data = (player_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(player_data_t));
    player_data_t *player2_data = (player_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(player_data_t));

    // inicializar los hilos
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        // inicializar y empezar la pelea para los pokemones del jugador 1
        player1_data[i].thread_num = i;
        player1_data[i].battle_data = shared_battle_data;
        player1_data[i].pokemon = player1->playerPokemons[i];
        player1_data[i].fighting_time = 0.0;
        player1_data[i].player = player1;
        pthread_create(&player1_threads[i], NULL, fight, (void *)&player1_data[i]);

        // inicializar y empezar la pelea para los pokemones del jugador 2
        player2_data[i].thread_num = i;
        player2_data[i].battle_data = shared_battle_data;
        player2_data[i].pokemon = player2->playerPokemons[i];
        player2_data[i].fighting_time = 0.0;
        player2_data[i].player = player2;
        pthread_create(&player2_threads[i], NULL, fight, (void *)&player2_data[i]);
    }

    // esperar por los hilos
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_join(player1_threads[i], NULL);
        pthread_join(player2_threads[i], NULL);
    }

    // parar el tiempo y calcular el tiempo que tardo la batalla
    shared_battle_data->end_time = clock();
    double execution_time = (double)(shared_battle_data->end_time - shared_battle_data->start_time) / CLOCKS_PER_SEC;
    printf("Duracion de la batalla: %f segundos\n", execution_time);

    // liberar datos
    pthread_mutex_destroy(&shared_battle_data->mutex);
    pthread_barrier_destroy(&shared_battle_data->barrier);
    pthread_cond_destroy(&shared_battle_data->condition);
    free(player1_data);
    free(player2_data);
    free(shared_battle_data);
    free(player1_threads);
    free(player2_threads);
}