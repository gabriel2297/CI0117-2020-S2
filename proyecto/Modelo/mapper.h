#ifndef MAPPER_H_
#define MAPPER_H_

#define NUM_POKEMON 50
#define NUM_MOVES 58
#define NUM_TYPES 18

/*
This code contains information about 50 Pokemon and their respective information for Pokemon Go Battles.
Before using any of the methods or arrays make sure to call 'initialize_data()'
To retrieve information about Pokemon, Moves or Types you can either call the methods or use the arrays directly.
For immunities, weaknesses and resistances use the corresponding matrixes defined in this file.
*/

typedef struct pokemon_info
{
    int id;
    char *speciesName;
    int fastMoveId;
    int chargedMoveId;
    int typeId;
} pokemon_info_t;

typedef struct move_info
{
    int id;
    int cooldown;
    char *moveName;
    int energy;
    int energyGain;
    int power;
    int typeId;
} move_info_t;

typedef struct type_info
{
    int id;
    char *typeName;
} type_info_t;

pokemon_info_t pokemon_info_list[NUM_POKEMON];
move_info_t move_info_list[NUM_MOVES];
type_info_t type_info_list[NUM_TYPES];

void initialize_data();

char* get_pokemon_species_name(int id);
int get_pokemon_type_id(int id);
int get_pokemon_fast_move_id(int id);
int get_pokemon_charged_move_id(int id);

char* get_move_name(int id);
int get_move_type_id(int id);
int get_move_cooldown(int id);
int get_move_power(int id);
int get_move_energy(int id);
int get_move_energy_gain(int id);

char* get_type_name(int id);

/* weaknesses_matrix[A][B], when TRUE, it means type A is weak agains type B (Or type B is effective agains type A) */
static const int weaknesses_matrix[NUM_TYPES][NUM_TYPES] = {{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0},{1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0},{0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0},{0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1},{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0},{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},{1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1},{0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0}};

/* resistances_matrix[A][B], when TRUE, it means type A resists moves of type B (Or type B is not very effective agains type A) */
static const int resistances_matrix[NUM_TYPES][NUM_TYPES] = {{0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1},{0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0},{1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},{1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0},{1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0},{0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0},{1,0,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0},{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1}};

/* immunities_matrix[A][B], when TRUE, it means type A is immune to type B (Or type B does not affect type A)*/
static const int immunities_matrix[NUM_TYPES][NUM_TYPES] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

#endif