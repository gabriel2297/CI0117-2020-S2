#include <stdio.h>
#include <stdlib.h>
#include "PlayerController.h"

void showPlayerInformation(player_t *player)
{
    printf("\nPokemones de %s:\n", player->nickname);
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        printf("\t- %s\n", player->playerPokemons[i]->pokemon_info->speciesName);
    }
}

void set_pokemon_player(player_t * player, int position, int pokemonId)
{
    initializePokemon(player->playerPokemons[position], pokemonId);

}

void initializePlayer(player_t *player)
{
   /*  printf("\nCual es el nombre del jugador? ");
    scanf("%29s", player->nickname);
    fflush(stdin); */
    // empezar a instanciar los pokemons del jugador
    /* printf("Ahora elija los pokemons de %s\n", player->nickname); */
    for (int i = 0; i < MAX_POKEMONS_PER_PLAYER; ++i)
    {
        player->playerPokemons[i] = (pokemon_t *)malloc(sizeof(pokemon_t));
        //getPokemonNumbersFromUser(player, i);
    }
}
