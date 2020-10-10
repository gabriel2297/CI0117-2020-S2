#include "../mapper.h"
#include <stdio.h>

void getAvailablePokemonModel()
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

void initializePokemonModel()
{
    initialize_data();
}

void printPokemonNameById(int id)
{
    printf("\t- %s\n", get_pokemon_species_name(id));
}