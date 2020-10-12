#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "../../Model/mapper.h"
#include "../PokemonController/PokemonController.h"

#define MAX_POKEMONS_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 30

typedef struct
{
    int playerId;
    char nickname[MAX_CHARS_PLAYER_NICKNAME];
    pokemon_t *playerPokemons[MAX_POKEMONS_PER_PLAYER];
} player_t;

void initializePlayer(player_t *player);
void showPlayerInformation(player_t *player);
void liberarMemoriaJugador(player_t *player);

#endif