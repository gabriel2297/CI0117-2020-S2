#include <stdio.h>
#include <bool.h>
#include "../PokemonModel/PokemonModel.h"

#define NUM_POKEMON_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 30
#define NUM_POKEMONS 50

typedef struct {
    size_t threadId;
    size_t pokemonId;
} pokemon_threadInfo_t;

typedef struct {
    size_t playerId;
    char nickname[MAX_CHARS_PLAYER_NICKNAME];
    pokemon_threadInfo_t* playerPokemons[];
} player_t;

void pickPokemonsForPlayer(player_t* player);
void showPokemonsForPlayer(player_t* player);
void pickNicknameForPlayer(player_t* player);
void getPokemonsFromUser(player_t* player);

void initPlayers()
{

    // crear los jugadores 
    player_t* player1 = malloc((size_t) sizeof(player_t));
    player_t* player2 = malloc((size_t) sizeof(player_t));
    player1->playerId = 1;
    player2->playerId = 2;

    // obtener la informacion de los jugadoes
    getPlayerNickname(player1);
    pickPokemonsForPlayer(player1);
    getPlayerNickname(player2);
    pickPokemonsForPlayer(player2);

    //TODO: empezar el juego

    // juego finalizo, liberar la memoria
    destroyPlayers(player1, player2);
}

void destroyPlayers(player_t* player1, player_t* player2){
    free(player1);
    free(player2);
}

/**
 * guardar el numero del pokemon en esta variable
 * restarle 1 ya que el arreglo empieza va de 0-49 y en pantalla
 * mostramos del 1-50.
 * @param player - recibimos un puntero al jugador que queremos inicializar
 **/
void pickPokemonsForPlayer(player_t* player)
{
    int pokemonNumber = 0;
    printf("\nElija el numero para el primer pokemon de %s: ", player->nickname);
    scanf("%d", pokemonNumber);
    --pokemonNumber;
    fflush(stdin);
}

/**
 * @param pokemonId - recibe el id del pokemon que queremos revisar si es valido
 * @returns true si es valido, false si es invalido
 **/
void checkValidPokemon(int* pokemonId) {
    while (1)
    {
        if (*pokemonId >= NUM_POKEMONS)
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\nError, Pokemon %i no existe.\n", (*pokemonId)+1);
            printf("\nElija un numero dentro de la lista de arriba: ");
        }
    }
}

void showPokemonsForPlayer(player_t* player)
{
    for (int i = 0; i < NUM_POKEMON_PER_PLAYER; ++i)
    {
        printf("\t%i) ", i + 1);
        printPokemonNameById(player->playerPokemons[i]->pokemonId);
    }
}

void getPlayerNickname(player_t* player)
{
    printf("\nCual es el nombre del jugador 1?");
    scanf("%29s", player->nickname);
    fflush(stdin);
}
