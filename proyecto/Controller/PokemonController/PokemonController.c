#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PokemonController.h"

#define BONUS 2.3

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

void loadPokemonMoves(move_info_t* chargedMove, move_info_t* fastMove)
{
    chargedMove->cooldown = get_move_cooldown(chargedMove->id);
    chargedMove->energy = get_move_energy(chargedMove->id);
    chargedMove->energyGain = get_move_energy_gain(chargedMove->id);
    chargedMove->moveName = get_move_name(chargedMove->id);
    chargedMove->power = get_move_power(chargedMove->id);
    chargedMove->typeId = get_move_type_id(chargedMove->id);
    fastMove->cooldown = get_move_cooldown(fastMove->id);
    fastMove->energy = get_move_energy(fastMove->id);
    fastMove->energyGain = get_move_energy_gain(fastMove->id);
    fastMove->moveName = get_move_name(fastMove->id);
    fastMove->power = get_move_power(fastMove->id);
    fastMove->typeId = get_move_type_id(chargedMove->id);
}

double calculateMoveEffectiveness(size_t target_pokemon_type, size_t attacking_move_type) 
{
    if (weaknesses_matrix[target_pokemon_type][attacking_move_type]) 
    {
        return 1.6;
    } 
    else if (resistances_matrix[target_pokemon_type][attacking_move_type]) 
    {
        return 0.625;
    } 
    else if (immunities_matrix[target_pokemon_type][attacking_move_type]) 
    {
        return 0.390625;
    } 
    else 
    {
        return 1;
    }
}

void doChargedMove(move_info_t* chargedMove, pokemon_t* opponentPokemon) 
{
    double effectiveness = calculateMoveEffectiveness(opponentPokemon->pokemon_info->typeId, chargedMove->typeId);
    double damage = floor(chargedMove->power * effectiveness * BONUS) + 1;
    opponentPokemon->hp -= damage;
    printf("\t> %s hp = %i after being damaged by %f\n", opponentPokemon->pokemon_info->speciesName, opponentPokemon->hp, damage);
}

void doFastMove(move_info_t* fastMove, pokemon_t* opponentPokemon)
{
    double effectiveness = calculateMoveEffectiveness(opponentPokemon->pokemon_info->typeId, fastMove->typeId);
    double damage = floor(fastMove->power * effectiveness * BONUS) + 1;
    opponentPokemon->hp -= damage;
    printf("\t> %s hp = %i after being damaged by %f\n", opponentPokemon->pokemon_info->speciesName, opponentPokemon->hp, damage);
}