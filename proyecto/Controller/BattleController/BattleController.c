#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
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
    thread_data_t *local_data = (thread_data_t *)args;
    shared_data_t *shared_data = local_data->shared_data;
    size_t thread_num = local_data->thread_num;
    int energyCharged = 0;
    player_t *player = local_data->player;
    player_t *opponent = local_data->opponent;
    pokemon_t *pokemon = player->playerPokemons[thread_num];
    pokemon_t *opponentPokemon;
    move_info_t *chargedMove = (move_info_t *)malloc(sizeof(move_info_t));
    move_info_t *fastMove = (move_info_t *)malloc(sizeof(move_info_t));
    chargedMove->id = pokemon->pokemon_info->chargedMoveId;
    fastMove->id = pokemon->pokemon_info->fastMoveId;
    loadPokemonMoves(chargedMove, fastMove);


    pthread_barrier_wait(&shared_data->barrier);
    pthread_mutex_lock(&shared_data->mutex);
    if (thread_num != player->pokemonTurn)
    {
        pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
    }

    pokemon->start_time = time(NULL);

    setPokemonName(player->playerId,pokemon->pokemon_info->speciesName);
    
    while (1)
    {
        if (player->playerId == shared_data->playerTurn)
        {
            if (pokemon->hp <= 0 || shared_data->isLast)
            {
                setPokemonHP(player->playerId, 0);
                pthread_mutex_unlock(&shared_data->mutex);
                break;
            }

            setPokemonHP(player->playerId, pokemon->hp);
            opponentPokemon = opponent->playerPokemons[opponent->pokemonTurn];

            if(energyCharged >= chargedMove->energy)
            {
                printf("%s:\n\t> %s atacando a %s con movimiento cargado!\n", player->nickname, pokemon->pokemon_info->speciesName, opponentPokemon->pokemon_info->speciesName);
                setChargedAttackName(player->playerId ,chargedMove->moveName, chargedMove->power);
                doChargedMove(chargedMove, opponentPokemon);
                energyCharged = 0;
                shared_data->playerTurn = opponent->playerId;
                pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
                //usleep(100*1000);
                usleep((chargedMove->cooldown * 1000));
            }
            else
            {
                printf("%s:\n\t> %s atacando a %s con movimiento rapido!\n", player->nickname, pokemon->pokemon_info->speciesName, opponentPokemon->pokemon_info->speciesName);
                setFastAttackName(player->playerId ,chargedMove->moveName, chargedMove->power);
                doFastMove(fastMove, opponentPokemon);
                energyCharged += fastMove->energyGain;
                shared_data->playerTurn = opponent->playerId;
                pthread_cond_signal(&opponent->condition[opponent->pokemonTurn]);
                //usleep(100*1000);
                usleep((fastMove->cooldown * 1000));
            }
            setPokemonEnergy(player->playerId, energyCharged);
            printf("\t> Energia acumulada de %s = %i. Ataque cargado = %i!\n", pokemon->pokemon_info->speciesName, energyCharged, chargedMove->energy);
            pthread_cond_wait(&player->condition[thread_num], &shared_data->mutex);
        }
        else 
        {
            setPokemonHP(player->playerId, pokemon->hp);
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
    pokemon->end_time = time(NULL);
    free(chargedMove);
    free(fastMove);
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
    unsigned long start_time = time(NULL);
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

    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        pthread_join(player1_threads[i], NULL);
        pthread_join(player2_threads[i], NULL);
    }

    // parar el tiempo y calcular el tiempo que tardo la batalla, aprovechar para destruir las variables de condicion
    unsigned long end_time = time(NULL) - start_time;
    printf("Duracion de la batalla: %lu segundos\n", end_time);
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {

        printf("\t- Pokemon %s del jugador %s duro %lu segundos en la batalla\n", player1->playerPokemons[i]->pokemon_info->speciesName, player1->nickname, (player1->playerPokemons[i]->end_time - player1->playerPokemons[i]->start_time) );
        pthread_cond_destroy(&player1->condition[i]);
        printf("\t- Pokemon %s del jugador %s duro %lu segundos en la batalla\n", player2->playerPokemons[i]->pokemon_info->speciesName, player2->nickname, (player2->playerPokemons[i]->end_time - player2->playerPokemons[i]->start_time) );
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