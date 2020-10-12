#include <stdio.h>
#include <stdlib.h>
#include "PokemonController.h"

void initializePokemon(pokemon_t *pokemon, int pokemonId)
{
    pokemon->hp = 1500;
    pokemon->pokemon_info = (pokemon_info_t *)malloc(sizeof(pokemon_info_t));
    pokemon->pokemon_info->id = pokemonId;
    pokemon->pokemon_info->chargedMoveId = get_pokemon_charged_move_id(pokemonId);
    pokemon->pokemon_info->fastMoveId = get_pokemon_fast_move_id(pokemonId);
    pokemon->pokemon_info->speciesName = get_pokemon_species_name(pokemonId);
    pokemon->pokemon_info->typeId = get_pokemon_type_id(pokemonId);
}

void showAvailablePokemons()
{
    for (int i = 0; i < NUM_POKEMON; i += 2)
    {
        if (i + 2 == NUM_POKEMON)
        {
            printf("\t%i) %s\t\t%i) %s\n", i + 1, get_pokemon_species_name(i), i + 2, get_pokemon_species_name(i + 1));
            break;
        }
        printf("\t%i) %s\t\t%i) %s\n", i + 1, get_pokemon_species_name(i), i + 2, get_pokemon_species_name(i + 1));
    }
}