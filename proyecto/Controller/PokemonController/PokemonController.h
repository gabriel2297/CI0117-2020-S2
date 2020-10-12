#ifndef POKEMONCONTROLLER_H_
#define POKEMONCONTROLLER_H_
#include "../../Model/mapper.h"

typedef struct
{
    int thread_id;
    pokemon_info_t *pokemon_info;
    int hp;
} pokemon_t;

void initializePokemon(pokemon_t *pokemon, int pokemonId);
void showAvailablePokemons();
void liberarMemoriaPokemonInfo(pokemon_info_t *pokemon_info);

#endif