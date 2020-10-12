#include <stdio.h>
#include <stdlib.h>
#include "PlayerController.h"

void liberarMemoriaJugador(player_t *player)
{
    for (size_t i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        liberarMemoriaPokemonInfo(player->playerPokemons[i]);
        free(player->playerPokemons[i]);
    }
}

void showPlayerInformation(player_t *player)
{
    printf("\e[1;1H\e[2J");
    printf("\nPokemones de %s:", player->nickname);
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        printf("\t- %s\n", player->playerPokemons[i]->pokemon_info->speciesName);
    }
}

void getPokemonNumbersFromUser(player_t *player, int position)
{
    printf("\e[1;1H\e[2J");
    showAvailablePokemons();
    int pokemonId = 0;
    printf("PokemonId is %i\n", pokemonId);
    switch (position)
    {
    case 0:
        printf("Primer pokemon: ");
        break;
    case 1:
        printf("Segundo pokemon: ");
        break;
    default:
        printf("Tercer pokemon: ");
        break;
    }
    while (1)
    {
        fflush(stdin);
        scanf("%i", &pokemonId);
        printf("Pokemon seleccionado = %i\n", pokemonId - 1);
        printf("Position = %i\n", position);
        if (position > 0)
        {
            printf("Id seleccionado en la posicion anterior: %i\n", player->playerPokemons[position - 1]->pokemon_info->id);
        }
        if (pokemonId > NUM_POKEMON)
        {
            printf("\nError, Pokemon %i no existe.\n", pokemonId);
            printf("\nElija un numero dentro de la lista de arriba: ");
        }
        else if (position > 0 && (pokemonId - 1 == player->playerPokemons[position - 1]->pokemon_info->id))
        {
            printf("\nError, el pokemon que eligio ya esta siendo usado.\n");
            printf("\nElija un nuevo pokemon: ");
        }
        else
        {
            break;
        }
    }
    --pokemonId;
    fflush(stdin);
    initializePokemon(player->playerPokemons[position], pokemonId);
    printf("\n");
}

void initializePlayer(player_t *player)
{
    printf("\nCual es el nombre del jugador? ");
    scanf("%29s", player->nickname);
    fflush(stdin);
    // empezar a instanciar los pokemons del jugador
    printf("Ahora elija los pokemons de %s\n", player->nickname);
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        player->playerPokemons[i] = (pokemon_t *)malloc(sizeof(pokemon_t));
        player->playerPokemons[i]->thread_id = i;
        getPokemonNumbersFromUser(player, i);
    }
}
