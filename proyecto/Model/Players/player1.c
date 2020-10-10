#include <stdio.h>
#include "../PokemonModel/PokemonModel.h"

#define NUM_POKEMON_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 15

int pokemonList[NUM_POKEMON_PER_PLAYER];
char nickname[MAX_CHARS_PLAYER_NICKNAME];

void pickPokemonsPlayer1();
void showPokemonsPlayer1();
void pickPlayer1Nickname();

void initPlayer1()
{
    pickPlayer1Nickname();
    pickPokemonsPlayer1();
    showPokemonsPlayer1();
}

void pickPokemonsPlayer1()
{
    printf("\n\nElija el numero para el primer pokemon de %s: ", nickname);
    scanf("%i", &pokemonList[0]);
    fflush(stdin);
    printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
    scanf("%i", &pokemonList[1]);
    fflush(stdin);
    while (1)
    {
        if (pokemonList[0] == pokemonList[1])
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\n\n\nError, %s no puede usar el mismo pokemon para el primer y segundo lugar! Vuelva a intentarlo.\n", nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%i", &pokemonList[1]);
            fflush(stdin);
        }
        else
        {
            break;
        }
    }
    printf("\nElija el numero para el tercer pokemon de %s: ", nickname);
    scanf("%i", &pokemonList[2]);
    fflush(stdin);
    while (1)
    {
        if (pokemonList[1] == pokemonList[2] || pokemonList[0] == pokemonList[2])
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\n\n\nError, %s no puede usar el mismo pokemon para el segundo y tercer lugar! Vuelva a intentarlo.\n", nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%i", &pokemonList[2]);
            fflush(stdin);
        }
        else
        {
            break;
        }
    }
}

void showPokemonsPlayer1()
{
    for (int i = 0; i < NUM_POKEMON_PER_PLAYER; ++i)
    {
        printPokemonNameById(pokemonList[i]);
    }
}

void pickPlayer1Nickname()
{
    printf("\n\nCual es el nombre del jugador 1? El nombre debe ser maximo de 14 caracteres: ");
    scanf("%14s", nickname);
    fflush(stdin);
}
