#ifndef INTERFACE_H
#define INTERFACE_H
#include <pthread.h>

pthread_mutex_t mutex;
void setPokemonName(int, char *);
char * getPokemonName();
char * getPokemon2Name();
void setPokemonHP(int, int);
void setPokemonEnergy(int, int);
void setFastAttackName(int playerId, char * moveName, int damage);
void setChargedAttackName(int playerId, char * moveName, int damage);
void setWinnerInformation(int, char *);
void setPokemonStatistics(unsigned long pokemon_statistics[3][3], pokemon_t* player1_pokemons[MAX_POKEMONS_PER_PLAYER], pokemon_t* player2_pokemons[MAX_POKEMONS_PER_PLAYER]);
#endif