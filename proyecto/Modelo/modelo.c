#include "mapper.h"
#include <stdio.h>

void getAvailablePokemonsModel()
{
    for (int i = 0; i < NUM_POKEMON; ++i)
    {
        printf("\t%i) %s\n", i + 1, get_pokemon_species_name(i));
    }
}

void initializePokemonsModel()
{
    initialize_data();
}