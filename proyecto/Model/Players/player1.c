#include <stdio.h>
#include "../PokemonModel/PokemonModel.h"

#define NUM_POKEMON_PER_PLAYER 3
#define MAX_CHARS_PLAYER_NICKNAME 30
#define NUM_POKEMONS 50

int pokemonList[NUM_POKEMON_PER_PLAYER];
char nickname[MAX_CHARS_PLAYER_NICKNAME];

void pickPokemonsPlayer1();
void showPokemonsPlayer1();
void pickPlayer1Nickname();
void getPokemonFromUser(int position, char *pokemonArray, char *pokemonNumber, char *playerName);

void initPlayer1()
{
    pickPlayer1Nickname();
    pickPokemonsPlayer1();
    showPokemonsPlayer1();
}

void getPokemonFromUser(int position, char *pokemonArray, char *pokemonNumber, char *playerName)
{
    printf("\nElija el numero para el %s pokemon de %s: ", pokemonNumber, nickname);
    scanf("%d", &pokemonList[position]);
    pokemonList[position] -= 1;
    fflush(stdin);
    while (1)
    {
        if (pokemonList[position] > NUM_POKEMONS)
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\nError, Pokemon %i no existe.\n", pokemonList[position]);
            printf("\nElija el numero para el %s pokemon de %s: ", pokemonNumber, nickname);
            scanf("%d", &pokemonList[1]);
            pokemonList[1] -= 1;
            fflush(stdin);
        }
    }
}

void pickPokemonsPlayer1()
{

    printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
    scanf("%d", &pokemonList[1]);
    pokemonList[1] -= 1;
    fflush(stdin);
    while (1)
    {
        if (pokemonList[1] > NUM_POKEMONS)
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\nError, Pokemon %i no existe.\n", pokemonList[1], nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%d", &pokemonList[1]);
            pokemonList[1] -= 1;
            fflush(stdin);
        }
        else if (pokemonList[0] == pokemonList[1])
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\nError, %s no puede usar el mismo pokemon para el primer y segundo lugar! Vuelva a intentarlo.\n", nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%d", &pokemonList[1]);
            pokemonList[1] -= 1;
            fflush(stdin);
        }
        else
        {
            break;
        }
    }
    printf("\nElija el numero para el tercer pokemon de %s: ", nickname);
    scanf("%d", &pokemonList[2]);
    pokemonList[2] -= 1;
    fflush(stdin);
    while (1)
    {
        if (pokemonList[1] == pokemonList[2])
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\n\n\nError, %s no puede usar el mismo pokemon para el segundo y tercer lugar! Vuelva a intentarlo.\n", nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%d", &pokemonList[2]);
            pokemonList[2] -= 1;
            fflush(stdin);
        }
        else if (pokemonList[0] == pokemonList[2])
        {
            printf("\e[1;1H\e[2J");
            getAvailablePokemonsModel();
            printf("\n\n\nError, %s no puede usar el mismo pokemon para el primero y tercer lugar! Vuelva a intentarlo.\n", nickname);
            printf("\nElija el numero para el segundo pokemon de %s: ", nickname);
            scanf("%d", &pokemonList[2]);
            pokemonList[2] -= 1;
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
        printf("\t%i) ", i + 1);
        printPokemonNameById(pokemonList[i]);
    }
}

void pickPlayer1Nickname()
{
    printf("\n\nCual es el nombre del jugador 1? El nombre debe ser maximo de 29 caracteres: ");
    scanf("%29s", nickname);
    fflush(stdin);
}
