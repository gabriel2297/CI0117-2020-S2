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

#endif