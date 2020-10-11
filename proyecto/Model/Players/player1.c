#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../PokemonModel/PokemonModel.h"

#define NUM_POKEMON_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 30
#define NUM_POKEMONS 50

typedef struct
{
    size_t threadId;
    size_t pokemonId;
} pokemon_threadInfo_t;

typedef struct
{
    size_t playerId;
    char nickname[MAX_CHARS_PLAYER_NICKNAME];
    pokemon_threadInfo_t *playerPokemons[NUM_POKEMON_PER_PLAYER];
} player_t;

void pickPokemonsForPlayer(player_t *player);
void showPokemonsForPlayer(player_t *player);
void getPlayerNickname(player_t *player);
void getPokemonsFromUser(player_t *player);
void destroyPlayers(player_t *player1, player_t *player2);
void checkValidPokemon(player_t *player, int position);
void initPlayers();

void initPlayers()
{
    // crear los jugadores
    player_t *player1 = (player_t *)malloc(sizeof(player_t));
    player_t *player2 = (player_t *)malloc(sizeof(player_t));
    player1->playerId = 1;
    player2->playerId = 2;
    for (int i = 0; i < NUM_POKEMON_PER_PLAYER; i++)
    {
        player1->playerPokemons[i] = (pokemon_threadInfo_t *)malloc(sizeof(pokemon_threadInfo_t));
        player2->playerPokemons[i] = (pokemon_threadInfo_t *)malloc(sizeof(pokemon_threadInfo_t));
    }

    // obtener la informacion de los jugadoes
    getPlayerNickname(player1);
    pickPokemonsForPlayer(player1);
    getPlayerNickname(player2);
    pickPokemonsForPlayer(player2);
    showPokemonsForPlayer(player1);
    showPokemonsForPlayer(player2);
    //TODO: empezar el juego

    // juego finalizo, liberar la memoria
    destroyPlayers(player1, player2);
}

/**
 * Los jugadores y los pokemones piden memoria por lo que hay que liberarla
 * @param player1 - puntero al jugador 1
 * @param player2 - puntero al jugador 2
 * */
void destroyPlayers(player_t *player1, player_t *player2)
{
    for (int i = 0; i < NUM_POKEMON_PER_PLAYER; ++i)
    {
        free(player1->playerPokemons[i]);
        free(player2->playerPokemons[i]);
    }
    free(player1);
    free(player2);
}

/**
 * guardar el numero del pokemon en esta variable
 * restarle 1 ya que el arreglo empieza va de 0-49 y en pantalla
 * mostramos del 1-50.
 * @param player - recibimos un puntero al jugador que queremos inicializar
 **/
void pickPokemonsForPlayer(player_t *player)
{
    printf("\nElija el numero para el primer pokemon de %s: ", player->nickname);
    scanf("%zu", &player->playerPokemons[0]->pokemonId);
    checkValidPokemon(player, 0);
    fflush(stdin);
    printf("\nElija el numero para el segundo pokemon de %s: ", player->nickname);
    scanf("%zu", &player->playerPokemons[1]->pokemonId);
    checkValidPokemon(player, 1);
    fflush(stdin);
    printf("\nElija el numero para el tercer pokemon de %s: ", player->nickname);
    scanf("%zu", &player->playerPokemons[2]->pokemonId);
    checkValidPokemon(player, 2);
    fflush(stdin);
    player->playerPokemons[0]->pokemonId--;
    player->playerPokemons[1]->pokemonId--;
    player->playerPokemons[2]->pokemonId--;
}

/**
 * @param pokemonId - recibe el id del pokemon que queremos revisar si es valido
 * @returns true si es valido, false si es invalido
 **/
void checkValidPokemon(player_t *player, int position)
{
    while (1)
    {
        printf("\e[1;1H\e[2J");
        getAvailablePokemonsModel();
        if (player->playerPokemons[position]->pokemonId >= NUM_POKEMONS)
        {
            printf("\nError, Pokemon %lu no existe.\n", (player->playerPokemons[position]->pokemonId) + 1);
            printf("\nElija un numero dentro de la lista de arriba: ");
        }
        else if (position > 0 && (player->playerPokemons[position]->pokemonId == player->playerPokemons[position - 1]->pokemonId))
        {
            printf("\nError, el pokemon que eligio ya esta siendo usado.\n");
            printf("\nElija un nuevo pokemon: ");
        }
        else
        {
            break;
        }
        scanf("%zu", &player->playerPokemons[position]->pokemonId);
        fflush(stdin);
    }
}

void showPokemonsForPlayer(player_t *player)
{
    printf("Mostrando pokemones elegidos por %s:\n", player->nickname);
    for (int i = 0; i < NUM_POKEMON_PER_PLAYER; ++i)
    {
        printf("\t%i) ", i + 1);
        printPokemonNameById(player->playerPokemons[i]->pokemonId);
    }
    printf("\n");
}

void getPlayerNickname(player_t *player)
{
    printf("\nCual es el nombre del jugador? ");
    scanf("%29s", player->nickname);
    fflush(stdin);
}
