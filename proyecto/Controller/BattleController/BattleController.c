#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "BattleController.h"

typedef struct
{
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
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

    // esperar en la barrera a que lleguen todos los hilos para asi empezar la batalla
    pthread_barrier_wait(&local_data->battle_data->barrier);

    // revisar si es turno de este hilo. Los pokemones se crean de manera secuencial, a como se ingresaron en el arreglo
    // (como los especifico el usuario), entonces el numero de hilo debe ser igual al numero del pokemon que esta compitiendo.
    // primero debemos obtener el lock, luego revisamos. Si no es nuestro turno, soltamos el lock y el hilo duerme
    pthread_mutex_lock(&shared_data->mutex);
    if (local_data->thread_num != local_data->player->turn)
    {
        pthread_cond_wait(&local_data->player->condition[local_data->thread_num], &shared_data->mutex);
    }

    // si llegamos hasta aqui es porque ya es turno de este hilo, empezar a contar cuanto dura en la batalla
    local_data->pokemon->start_time = clock();

    // imprimir para probar que funciona hasta aca
    printf("Hola desde hilo %zu - Pokemon %s\n", local_data->thread_num, local_data->pokemon->pokemon_info->speciesName);
    //Mientras la vida del pokemon sea mayor a 0
    // while (local_data->pokemon->hp > 0)
    // {
    //     // utilizar un semaforo para decidir quien sigue atacando (similar al problema del productor/consumidor)
    //     // agarrar el mutex para atacar
    //     // liberar el mutex para atacar
    //     // hacer el post
    // }

    //pokemon murio, aumentar el contador, soltar el mutex, despertar al siguiente hilo y guardar cuando el hilo finalizo
    ++local_data->player->turn;
    pthread_mutex_unlock(&shared_data->mutex);
    pthread_cond_signal(&local_data->player->condition[local_data->player->turn]);
    local_data->pokemon->end_time = clock();

    return NULL;
}

void initBattle(player_t *player1, player_t *player2)
{
    // crear los hilos de los jugadores
    pthread_t *player1_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));
    pthread_t *player2_threads = (pthread_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(pthread_t));

    // crear los datos compartidos por los hilos
    battle_data_t *shared_battle_data = (battle_data_t *)malloc((MAX_POKEMONS_PER_PLAYER * 2) * sizeof(battle_data_t));

    // inicializar los metodos de sincronizacion
    pthread_mutex_init(&shared_battle_data->mutex, NULL);
    pthread_barrier_init(&shared_battle_data->barrier, NULL, (MAX_POKEMONS_PER_PLAYER * 2));

    // crear los datos necesarios por hilo
    player_data_t *player1_data = (player_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(player_data_t));
    player_data_t *player2_data = (player_data_t *)malloc(MAX_POKEMONS_PER_PLAYER * sizeof(player_data_t));

    // inicializar los hilos
    clock_t start_time = clock();
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        // inicializar la variable de condicion para cada hilo
        // inicializar y empezar la pelea para los pokemones del jugador 1
        player1_data[i].thread_num = i;
        player1_data[i].battle_data = shared_battle_data;
        player1_data[i].pokemon = player1->playerPokemons[i];
        player1_data[i].fighting_time = 0.0;
        player1_data[i].player = player1;
        pthread_cond_init(&player1->condition[i], NULL);
        pthread_create(&player1_threads[i], NULL, fight, (void *)&player1_data[i]);

        // inicializar y empezar la pelea para los pokemones del jugador 2
        player2_data[i].thread_num = i;
        player2_data[i].battle_data = shared_battle_data;
        player2_data[i].pokemon = player2->playerPokemons[i];
        player2_data[i].fighting_time = 0.0;
        player2_data[i].player = player2;
        pthread_cond_init(&player2->condition[i], NULL);
        pthread_create(&player2_threads[i], NULL, fight, (void *)&player2_data[i]);
    }

    // esperar por los hilos
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_join(player1_threads[i], NULL);
        pthread_join(player2_threads[i], NULL);
    }

    // parar el tiempo y calcular el tiempo que tardo la batalla, aprovechar para destruir las variables de condicion
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Duracion de la batalla: %f segundos\n", execution_time);
    for (int i = 0; i < (MAX_POKEMONS_PER_PLAYER * 2); ++i)
    {
        printf("\t- Pokemon %s del jugador %s duro %f en la batalla\n", player1->playerPokemons[i]->pokemon_info->speciesName, player1->nickname, ((player1->playerPokemons[i]->end_time - player1->playerPokemons[i]->end_time) / CLOCKS_PER_SEC));
        pthread_cond_destroy(&player1->condition[i]);
        printf("\t- Pokemon %s del jugador %s duro %f en la batalla\n", player2->playerPokemons[i]->pokemon_info->speciesName, player2->nickname, ((player2->playerPokemons[i]->end_time - player2->playerPokemons[i]->end_time) / CLOCKS_PER_SEC));
        pthread_cond_destroy(&player2->condition[i]);
    }

    // liberar datos
    pthread_mutex_destroy(&shared_battle_data->mutex);
    pthread_barrier_destroy(&shared_battle_data->barrier);
    free(player1_data);
    free(player2_data);
    free(shared_battle_data);
    free(player1_threads);
    free(player2_threads);
}