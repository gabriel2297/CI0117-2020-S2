#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "../PokemonController/PokemonController.h"

#define MAX_POKEMONS_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 30

typedef struct
{
    int playerId;
    size_t pokemonTurn;
    char nickname[MAX_CHARS_PLAYER_NICKNAME];
    pokemon_t *playerPokemons[MAX_POKEMONS_PER_PLAYER];
    pthread_cond_t *condition;
} player_t;

void initializePlayer(player_t *player);
void showPlayerInformation(player_t *player);
void liberarMemoriaJugador(player_t *player);
void set_pokemon_player(player_t * player, int position, int pokemonId);
#endif