#ifndef POKEMONCONTROLLER_H_
#define POKEMONCONTROLLER_H_

#include "../../Model/mapper.h"
#include <time.h>

typedef struct
{
    unsigned long start_time;
    unsigned long end_time;
    pokemon_info_t *pokemon_info;
    int hp;
} pokemon_t;

void initializePokemon(pokemon_t *pokemon, int pokemonId);
void showAvailablePokemons();
void loadPokemonMoves(move_info_t* chargedMove, move_info_t* fastMove);
void liberarMemoriaPokemonInfo(pokemon_info_t *pokemon_info);
void doChargedMove(move_info_t* chargedMove, pokemon_t* opponentPokemon);
void doFastMove(move_info_t* fastMove, pokemon_t* opponentPokemon);

#endif