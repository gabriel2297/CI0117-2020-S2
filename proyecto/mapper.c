#include "mapper.h"

char *get_pokemon_species_name(int id)
{
    return pokemon_info_list[id].speciesName;
}

int get_pokemon_type_id(int id)
{
    return pokemon_info_list[id].typeId;
}

int get_pokemon_fast_move_id(int id)
{
    return pokemon_info_list[id].fastMoveId;
}

int get_pokemon_charged_move_id(int id)
{
    return pokemon_info_list[id].chargedMoveId;
}

char *get_move_name(int id)
{
    return move_info_list[id].moveName;
}

int get_move_type_id(int id)
{
    return move_info_list[id].typeId;
}

int get_move_cooldown(int id)
{
    return move_info_list[id].cooldown;
}

int get_move_power(int id)
{
    return move_info_list[id].power;
}

int get_move_energy(int id)
{
    return move_info_list[id].energy;
}

int get_move_energy_gain(int id)
{
    return move_info_list[id].energyGain;
}

char *get_type_name(int id)
{
    return type_info_list[id].typeName;
}

void set_pokemon_info(int id)
{
    switch (id)
    {
    case 0:
        pokemon_info_list[id].id = 0;
        pokemon_info_list[id].speciesName = "venusaur";
        pokemon_info_list[id].chargedMoveId = 35;
        pokemon_info_list[id].fastMoveId = 50;
        pokemon_info_list[id].typeId = 9;
        break;
    case 1:
        pokemon_info_list[id].id = 1;
        pokemon_info_list[id].speciesName = "wigglytuff";
        pokemon_info_list[id].chargedMoveId = 22;
        pokemon_info_list[id].fastMoveId = 30;
        pokemon_info_list[id].typeId = 12;
        break;
    case 2:
        pokemon_info_list[id].id = 2;
        pokemon_info_list[id].speciesName = "gloom";
        pokemon_info_list[id].chargedMoveId = 45;
        pokemon_info_list[id].fastMoveId = 0;
        pokemon_info_list[id].typeId = 9;
        break;
    case 3:
        pokemon_info_list[id].id = 3;
        pokemon_info_list[id].speciesName = "primeape";
        pokemon_info_list[id].chargedMoveId = 16;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 5;
        break;
    case 4:
        pokemon_info_list[id].id = 4;
        pokemon_info_list[id].speciesName = "machamp";
        pokemon_info_list[id].chargedMoveId = 16;
        pokemon_info_list[id].fastMoveId = 12;
        pokemon_info_list[id].typeId = 5;
        break;
    case 5:
        pokemon_info_list[id].id = 5;
        pokemon_info_list[id].speciesName = "victreebel";
        pokemon_info_list[id].chargedMoveId = 42;
        pokemon_info_list[id].fastMoveId = 0;
        pokemon_info_list[id].typeId = 9;
        break;
    case 6:
        pokemon_info_list[id].id = 6;
        pokemon_info_list[id].speciesName = "dewgong";
        pokemon_info_list[id].chargedMoveId = 5;
        pokemon_info_list[id].fastMoveId = 36;
        pokemon_info_list[id].typeId = 17;
        break;
    case 7:
        pokemon_info_list[id].id = 7;
        pokemon_info_list[id].speciesName = "lickitung";
        pokemon_info_list[id].chargedMoveId = 40;
        pokemon_info_list[id].fastMoveId = 43;
        pokemon_info_list[id].typeId = 12;
        break;
    case 8:
        pokemon_info_list[id].id = 8;
        pokemon_info_list[id].speciesName = "lapras";
        pokemon_info_list[id].chargedMoveId = 8;
        pokemon_info_list[id].fastMoveId = 36;
        pokemon_info_list[id].typeId = 17;
        break;
    case 9:
        pokemon_info_list[id].id = 9;
        pokemon_info_list[id].speciesName = "snorlax";
        pokemon_info_list[id].chargedMoveId = 9;
        pokemon_info_list[id].fastMoveId = 43;
        pokemon_info_list[id].typeId = 12;
        break;
    case 10:
        pokemon_info_list[id].id = 10;
        pokemon_info_list[id].speciesName = "zapdos";
        pokemon_info_list[id].chargedMoveId = 53;
        pokemon_info_list[id].fastMoveId = 14;
        pokemon_info_list[id].typeId = 3;
        break;
    case 11:
        pokemon_info_list[id].id = 11;
        pokemon_info_list[id].speciesName = "mew";
        pokemon_info_list[id].chargedMoveId = 4;
        pokemon_info_list[id].fastMoveId = 14;
        pokemon_info_list[id].typeId = 14;
        break;
    case 12:
        pokemon_info_list[id].id = 12;
        pokemon_info_list[id].speciesName = "meganium";
        pokemon_info_list[id].chargedMoveId = 28;
        pokemon_info_list[id].fastMoveId = 50;
        pokemon_info_list[id].typeId = 9;
        break;
    case 13:
        pokemon_info_list[id].id = 13;
        pokemon_info_list[id].speciesName = "lanturn";
        pokemon_info_list[id].chargedMoveId = 39;
        pokemon_info_list[id].fastMoveId = 14;
        pokemon_info_list[id].typeId = 17;
        break;
    case 14:
        pokemon_info_list[id].id = 14;
        pokemon_info_list[id].speciesName = "bellossom";
        pokemon_info_list[id].chargedMoveId = 22;
        pokemon_info_list[id].fastMoveId = 0;
        pokemon_info_list[id].typeId = 9;
        break;
    case 15:
        pokemon_info_list[id].id = 15;
        pokemon_info_list[id].speciesName = "azumarill";
        pokemon_info_list[id].chargedMoveId = 39;
        pokemon_info_list[id].fastMoveId = 11;
        pokemon_info_list[id].typeId = 17;
        break;
    case 16:
        pokemon_info_list[id].id = 16;
        pokemon_info_list[id].speciesName = "politoed";
        pokemon_info_list[id].chargedMoveId = 8;
        pokemon_info_list[id].fastMoveId = 11;
        pokemon_info_list[id].typeId = 17;
        break;
    case 17:
        pokemon_info_list[id].id = 17;
        pokemon_info_list[id].speciesName = "umbreon";
        pokemon_info_list[id].chargedMoveId = 21;
        pokemon_info_list[id].fastMoveId = 30;
        pokemon_info_list[id].typeId = 1;
        break;
    case 18:
        pokemon_info_list[id].id = 18;
        pokemon_info_list[id].speciesName = "mantine";
        pokemon_info_list[id].chargedMoveId = 2;
        pokemon_info_list[id].fastMoveId = 11;
        pokemon_info_list[id].typeId = 17;
        break;
    case 19:
        pokemon_info_list[id].id = 19;
        pokemon_info_list[id].speciesName = "skarmory";
        pokemon_info_list[id].chargedMoveId = 10;
        pokemon_info_list[id].fastMoveId = 3;
        pokemon_info_list[id].typeId = 16;
        break;
    case 20:
        pokemon_info_list[id].id = 20;
        pokemon_info_list[id].speciesName = "hitmontop";
        pokemon_info_list[id].chargedMoveId = 16;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 5;
        break;
    case 21:
        pokemon_info_list[id].id = 21;
        pokemon_info_list[id].speciesName = "raikou";
        pokemon_info_list[id].chargedMoveId = 52;
        pokemon_info_list[id].fastMoveId = 54;
        pokemon_info_list[id].typeId = 3;
        break;
    case 22:
        pokemon_info_list[id].id = 22;
        pokemon_info_list[id].speciesName = "swampert";
        pokemon_info_list[id].chargedMoveId = 28;
        pokemon_info_list[id].fastMoveId = 47;
        pokemon_info_list[id].typeId = 17;
        break;
    case 23:
        pokemon_info_list[id].id = 23;
        pokemon_info_list[id].speciesName = "shiftry";
        pokemon_info_list[id].chargedMoveId = 34;
        pokemon_info_list[id].fastMoveId = 30;
        pokemon_info_list[id].typeId = 9;
        break;
    case 24:
        pokemon_info_list[id].id = 24;
        pokemon_info_list[id].speciesName = "pelipper";
        pokemon_info_list[id].chargedMoveId = 8;
        pokemon_info_list[id].fastMoveId = 56;
        pokemon_info_list[id].typeId = 17;
        break;
    case 25:
        pokemon_info_list[id].id = 25;
        pokemon_info_list[id].speciesName = "vigoroth";
        pokemon_info_list[id].chargedMoveId = 9;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 12;
        break;
    case 26:
        pokemon_info_list[id].id = 26;
        pokemon_info_list[id].speciesName = "medicham";
        pokemon_info_list[id].chargedMoveId = 27;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 5;
        break;
    case 27:
        pokemon_info_list[id].id = 27;
        pokemon_info_list[id].speciesName = "flygon";
        pokemon_info_list[id].chargedMoveId = 24;
        pokemon_info_list[id].fastMoveId = 26;
        pokemon_info_list[id].typeId = 10;
        break;
    case 28:
        pokemon_info_list[id].id = 28;
        pokemon_info_list[id].speciesName = "altaria";
        pokemon_info_list[id].chargedMoveId = 22;
        pokemon_info_list[id].fastMoveId = 23;
        pokemon_info_list[id].typeId = 2;
        break;
    case 29:
        pokemon_info_list[id].id = 29;
        pokemon_info_list[id].speciesName = "whiscash";
        pokemon_info_list[id].chargedMoveId = 8;
        pokemon_info_list[id].fastMoveId = 47;
        pokemon_info_list[id].typeId = 17;
        break;
    case 30:
        pokemon_info_list[id].id = 30;
        pokemon_info_list[id].speciesName = "castform";
        pokemon_info_list[id].chargedMoveId = 29;
        pokemon_info_list[id].fastMoveId = 38;
        pokemon_info_list[id].typeId = 12;
        break;
    case 31:
        pokemon_info_list[id].id = 31;
        pokemon_info_list[id].speciesName = "tropius";
        pokemon_info_list[id].chargedMoveId = 2;
        pokemon_info_list[id].fastMoveId = 3;
        pokemon_info_list[id].typeId = 9;
        break;
    case 32:
        pokemon_info_list[id].id = 32;
        pokemon_info_list[id].speciesName = "regirock";
        pokemon_info_list[id].chargedMoveId = 33;
        pokemon_info_list[id].fastMoveId = 51;
        pokemon_info_list[id].typeId = 15;
        break;
    case 33:
        pokemon_info_list[id].id = 33;
        pokemon_info_list[id].speciesName = "registeel";
        pokemon_info_list[id].chargedMoveId = 32;
        pokemon_info_list[id].fastMoveId = 44;
        pokemon_info_list[id].typeId = 16;
        break;
    case 34:
        pokemon_info_list[id].id = 34;
        pokemon_info_list[id].speciesName = "deoxys";
        pokemon_info_list[id].chargedMoveId = 40;
        pokemon_info_list[id].fastMoveId = 14;
        pokemon_info_list[id].typeId = 14;
        break;
    case 35:
        pokemon_info_list[id].id = 35;
        pokemon_info_list[id].speciesName = "grotle";
        pokemon_info_list[id].chargedMoveId = 9;
        pokemon_info_list[id].fastMoveId = 7;
        pokemon_info_list[id].typeId = 9;
        break;
    case 36:
        pokemon_info_list[id].id = 36;
        pokemon_info_list[id].speciesName = "bastiodon";
        pokemon_info_list[id].chargedMoveId = 31;
        pokemon_info_list[id].fastMoveId = 41;
        pokemon_info_list[id].typeId = 15;
        break;
    case 37:
        pokemon_info_list[id].id = 37;
        pokemon_info_list[id].speciesName = "munchlax";
        pokemon_info_list[id].chargedMoveId = 9;
        pokemon_info_list[id].fastMoveId = 43;
        pokemon_info_list[id].typeId = 12;
        break;
    case 38:
        pokemon_info_list[id].id = 38;
        pokemon_info_list[id].speciesName = "abomasnow";
        pokemon_info_list[id].chargedMoveId = 8;
        pokemon_info_list[id].fastMoveId = 48;
        pokemon_info_list[id].typeId = 9;
        break;
    case 39:
        pokemon_info_list[id].id = 39;
        pokemon_info_list[id].speciesName = "magnezone";
        pokemon_info_list[id].chargedMoveId = 32;
        pokemon_info_list[id].fastMoveId = 14;
        pokemon_info_list[id].typeId = 3;
        break;
    case 40:
        pokemon_info_list[id].id = 40;
        pokemon_info_list[id].speciesName = "cresselia";
        pokemon_info_list[id].chargedMoveId = 6;
        pokemon_info_list[id].fastMoveId = 17;
        pokemon_info_list[id].typeId = 14;
        break;
    case 41:
        pokemon_info_list[id].id = 41;
        pokemon_info_list[id].speciesName = "leavanny";
        pokemon_info_list[id].chargedMoveId = 42;
        pokemon_info_list[id].fastMoveId = 50;
        pokemon_info_list[id].typeId = 0;
        break;
    case 42:
        pokemon_info_list[id].id = 42;
        pokemon_info_list[id].speciesName = "whimsicott";
        pokemon_info_list[id].chargedMoveId = 37;
        pokemon_info_list[id].fastMoveId = 15;
        pokemon_info_list[id].typeId = 9;
        break;
    case 43:
        pokemon_info_list[id].id = 43;
        pokemon_info_list[id].speciesName = "scrafty";
        pokemon_info_list[id].chargedMoveId = 1;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 1;
        break;
    case 44:
        pokemon_info_list[id].id = 44;
        pokemon_info_list[id].speciesName = "alomomola";
        pokemon_info_list[id].chargedMoveId = 39;
        pokemon_info_list[id].fastMoveId = 57;
        pokemon_info_list[id].typeId = 17;
        break;
    case 45:
        pokemon_info_list[id].id = 45;
        pokemon_info_list[id].speciesName = "galvantula";
        pokemon_info_list[id].chargedMoveId = 20;
        pokemon_info_list[id].fastMoveId = 55;
        pokemon_info_list[id].typeId = 0;
        break;
    case 46:
        pokemon_info_list[id].id = 46;
        pokemon_info_list[id].speciesName = "ferrothorn";
        pokemon_info_list[id].chargedMoveId = 49;
        pokemon_info_list[id].fastMoveId = 13;
        pokemon_info_list[id].typeId = 9;
        break;
    case 47:
        pokemon_info_list[id].id = 47;
        pokemon_info_list[id].speciesName = "stunfisk";
        pokemon_info_list[id].chargedMoveId = 46;
        pokemon_info_list[id].fastMoveId = 54;
        pokemon_info_list[id].typeId = 10;
        break;
    case 48:
        pokemon_info_list[id].id = 48;
        pokemon_info_list[id].speciesName = "zweilous";
        pokemon_info_list[id].chargedMoveId = 25;
        pokemon_info_list[id].fastMoveId = 7;
        pokemon_info_list[id].typeId = 1;
        break;
    case 49:
        pokemon_info_list[id].id = 49;
        pokemon_info_list[id].speciesName = "obstagoon";
        pokemon_info_list[id].chargedMoveId = 19;
        pokemon_info_list[id].fastMoveId = 18;
        pokemon_info_list[id].typeId = 1;
        break;
    }
}

void set_move_info(int id)
{
    switch (id)
    {
    case 0:
        move_info_list[id].id = 0;
        move_info_list[id].moveName = "ACID";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 5;
        move_info_list[id].power = 6;
        move_info_list[id].typeId = 13;
        break;
    case 1:
        move_info_list[id].id = 1;
        move_info_list[id].moveName = "ACID_SPRAY";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 50;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 20;
        move_info_list[id].typeId = 13;
        break;
    case 2:
        move_info_list[id].id = 2;
        move_info_list[id].moveName = "AERIAL_ACE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 55;
        move_info_list[id].typeId = 7;
        break;
    case 3:
        move_info_list[id].id = 3;
        move_info_list[id].moveName = "AIR_SLASH";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 9;
        move_info_list[id].power = 9;
        move_info_list[id].typeId = 7;
        break;
    case 4:
        move_info_list[id].id = 4;
        move_info_list[id].moveName = "ANCIENT_POWER";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 45;
        move_info_list[id].typeId = 15;
        break;
    case 5:
        move_info_list[id].id = 5;
        move_info_list[id].moveName = "AQUA_JET";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 45;
        move_info_list[id].typeId = 17;
        break;
    case 6:
        move_info_list[id].id = 6;
        move_info_list[id].moveName = "AURORA_BEAM";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 60;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 80;
        move_info_list[id].typeId = 11;
        break;
    case 7:
        move_info_list[id].id = 7;
        move_info_list[id].moveName = "BITE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 2;
        move_info_list[id].power = 4;
        move_info_list[id].typeId = 1;
        break;
    case 8:
        move_info_list[id].id = 8;
        move_info_list[id].moveName = "BLIZZARD";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 75;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 140;
        move_info_list[id].typeId = 11;
        break;
    case 9:
        move_info_list[id].id = 9;
        move_info_list[id].moveName = "BODY_SLAM";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 35;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 60;
        move_info_list[id].typeId = 12;
        break;
    case 10:
        move_info_list[id].id = 10;
        move_info_list[id].moveName = "BRAVE_BIRD";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 55;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 130;
        move_info_list[id].typeId = 7;
        break;
    case 11:
        move_info_list[id].id = 11;
        move_info_list[id].moveName = "BUBBLE";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 11;
        move_info_list[id].power = 8;
        move_info_list[id].typeId = 17;
        break;
    case 12:
        move_info_list[id].id = 12;
        move_info_list[id].moveName = "BULLET_PUNCH";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 7;
        move_info_list[id].power = 6;
        move_info_list[id].typeId = 16;
        break;
    case 13:
        move_info_list[id].id = 13;
        move_info_list[id].moveName = "BULLET_SEED";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 13;
        move_info_list[id].power = 5;
        move_info_list[id].typeId = 9;
        break;
    case 14:
        move_info_list[id].id = 14;
        move_info_list[id].moveName = "CHARGE_BEAM";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 11;
        move_info_list[id].power = 5;
        move_info_list[id].typeId = 3;
        break;
    case 15:
        move_info_list[id].id = 15;
        move_info_list[id].moveName = "CHARM";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 6;
        move_info_list[id].power = 16;
        move_info_list[id].typeId = 4;
        break;
    case 16:
        move_info_list[id].id = 16;
        move_info_list[id].moveName = "CLOSE_COMBAT";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 100;
        move_info_list[id].typeId = 5;
        break;
    case 17:
        move_info_list[id].id = 17;
        move_info_list[id].moveName = "CONFUSION";
        move_info_list[id].cooldown = 2000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 12;
        move_info_list[id].power = 16;
        move_info_list[id].typeId = 14;
        break;
    case 18:
        move_info_list[id].id = 18;
        move_info_list[id].moveName = "COUNTER";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 7;
        move_info_list[id].power = 8;
        move_info_list[id].typeId = 5;
        break;
    case 19:
        move_info_list[id].id = 19;
        move_info_list[id].moveName = "CROSS_CHOP";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 35;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 50;
        move_info_list[id].typeId = 5;
        break;
    case 20:
        move_info_list[id].id = 20;
        move_info_list[id].moveName = "CROSS_POISON";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 35;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 40;
        move_info_list[id].typeId = 13;
        break;
    case 21:
        move_info_list[id].id = 21;
        move_info_list[id].moveName = "DARK_PULSE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 50;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 80;
        move_info_list[id].typeId = 1;
        break;
    case 22:
        move_info_list[id].id = 22;
        move_info_list[id].moveName = "DAZZLING_GLEAM";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 70;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 110;
        move_info_list[id].typeId = 4;
        break;
    case 23:
        move_info_list[id].id = 23;
        move_info_list[id].moveName = "DRAGON_BREATH";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 3;
        move_info_list[id].power = 4;
        move_info_list[id].typeId = 2;
        break;
    case 24:
        move_info_list[id].id = 24;
        move_info_list[id].moveName = "DRAGON_CLAW";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 35;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 50;
        move_info_list[id].typeId = 2;
        break;
    case 25:
        move_info_list[id].id = 25;
        move_info_list[id].moveName = "DRAGON_PULSE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 60;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 2;
        break;
    case 26:
        move_info_list[id].id = 26;
        move_info_list[id].moveName = "DRAGON_TAIL";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 10;
        move_info_list[id].power = 9;
        move_info_list[id].typeId = 2;
        break;
    case 27:
        move_info_list[id].id = 27;
        move_info_list[id].moveName = "DYNAMIC_PUNCH";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 50;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 5;
        break;
    case 28:
        move_info_list[id].id = 28;
        move_info_list[id].moveName = "EARTHQUAKE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 65;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 120;
        move_info_list[id].typeId = 10;
        break;
    case 29:
        move_info_list[id].id = 29;
        move_info_list[id].moveName = "ENERGY_BALL";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 55;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 9;
        break;
    case 30:
        move_info_list[id].id = 30;
        move_info_list[id].moveName = "FEINT_ATTACK";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 6;
        move_info_list[id].power = 6;
        move_info_list[id].typeId = 1;
        break;
    case 31:
        move_info_list[id].id = 31;
        move_info_list[id].moveName = "FLAMETHROWER";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 55;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 6;
        break;
    case 32:
        move_info_list[id].id = 32;
        move_info_list[id].moveName = "FLASH_CANNON";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 70;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 110;
        move_info_list[id].typeId = 16;
        break;
    case 33:
        move_info_list[id].id = 33;
        move_info_list[id].moveName = "FOCUS_BLAST";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 75;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 140;
        move_info_list[id].typeId = 5;
        break;
    case 34:
        move_info_list[id].id = 34;
        move_info_list[id].moveName = "FOUL_PLAY";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 70;
        move_info_list[id].typeId = 1;
        break;
    case 35:
        move_info_list[id].id = 35;
        move_info_list[id].moveName = "FRENZY_PLANT";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 45;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 100;
        move_info_list[id].typeId = 9;
        break;
    case 36:
        move_info_list[id].id = 36;
        move_info_list[id].moveName = "FROST_BREATH";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 5;
        move_info_list[id].power = 7;
        move_info_list[id].typeId = 11;
        break;
    case 37:
        move_info_list[id].id = 37;
        move_info_list[id].moveName = "GRASS_KNOT";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 50;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 9;
        break;
    case 38:
        move_info_list[id].id = 38;
        move_info_list[id].moveName = "HEX";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 12;
        move_info_list[id].power = 6;
        move_info_list[id].typeId = 8;
        break;
    case 39:
        move_info_list[id].id = 39;
        move_info_list[id].moveName = "HYDRO_PUMP";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 75;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 130;
        move_info_list[id].typeId = 17;
        break;
    case 40:
        move_info_list[id].id = 40;
        move_info_list[id].moveName = "HYPER_BEAM";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 80;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 150;
        move_info_list[id].typeId = 12;
        break;
    case 41:
        move_info_list[id].id = 41;
        move_info_list[id].moveName = "IRON_TAIL";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 6;
        move_info_list[id].power = 9;
        move_info_list[id].typeId = 16;
        break;
    case 42:
        move_info_list[id].id = 42;
        move_info_list[id].moveName = "LEAF_BLADE";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 35;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 70;
        move_info_list[id].typeId = 9;
        break;
    case 43:
        move_info_list[id].id = 43;
        move_info_list[id].moveName = "LICK";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 3;
        move_info_list[id].power = 3;
        move_info_list[id].typeId = 8;
        break;
    case 44:
        move_info_list[id].id = 44;
        move_info_list[id].moveName = "METAL_CLAW";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 6;
        move_info_list[id].power = 5;
        move_info_list[id].typeId = 16;
        break;
    case 45:
        move_info_list[id].id = 45;
        move_info_list[id].moveName = "MOONBLAST";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 60;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 110;
        move_info_list[id].typeId = 4;
        break;
    case 46:
        move_info_list[id].id = 46;
        move_info_list[id].moveName = "MUD_BOMB";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 40;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 55;
        move_info_list[id].typeId = 10;
        break;
    case 47:
        move_info_list[id].id = 47;
        move_info_list[id].moveName = "MUD_SHOT";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 9;
        move_info_list[id].power = 3;
        move_info_list[id].typeId = 10;
        break;
    case 48:
        move_info_list[id].id = 48;
        move_info_list[id].moveName = "POWDER_SNOW";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 8;
        move_info_list[id].power = 5;
        move_info_list[id].typeId = 11;
        break;
    case 49:
        move_info_list[id].id = 49;
        move_info_list[id].moveName = "POWER_WHIP";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 50;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 90;
        move_info_list[id].typeId = 9;
        break;
    case 50:
        move_info_list[id].id = 50;
        move_info_list[id].moveName = "RAZOR_LEAF";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 4;
        move_info_list[id].power = 11;
        move_info_list[id].typeId = 9;
        break;
    case 51:
        move_info_list[id].id = 51;
        move_info_list[id].moveName = "ROCK_SMASH";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 7;
        move_info_list[id].power = 9;
        move_info_list[id].typeId = 5;
        break;
    case 52:
        move_info_list[id].id = 52;
        move_info_list[id].moveName = "SHADOW_BALL";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 55;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 100;
        move_info_list[id].typeId = 8;
        break;
    case 53:
        move_info_list[id].id = 53;
        move_info_list[id].moveName = "THUNDER";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 60;
        move_info_list[id].energyGain = 0;
        move_info_list[id].power = 100;
        move_info_list[id].typeId = 3;
        break;
    case 54:
        move_info_list[id].id = 54;
        move_info_list[id].moveName = "THUNDER_SHOCK";
        move_info_list[id].cooldown = 1000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 9;
        move_info_list[id].power = 3;
        move_info_list[id].typeId = 3;
        break;
    case 55:
        move_info_list[id].id = 55;
        move_info_list[id].moveName = "VOLT_SWITCH";
        move_info_list[id].cooldown = 2000;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 16;
        move_info_list[id].power = 12;
        move_info_list[id].typeId = 3;
        break;
    case 56:
        move_info_list[id].id = 56;
        move_info_list[id].moveName = "WATER_GUN";
        move_info_list[id].cooldown = 500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 3;
        move_info_list[id].power = 3;
        move_info_list[id].typeId = 17;
        break;
    case 57:
        move_info_list[id].id = 57;
        move_info_list[id].moveName = "WATERFALL";
        move_info_list[id].cooldown = 1500;
        move_info_list[id].energy = 0;
        move_info_list[id].energyGain = 8;
        move_info_list[id].power = 12;
        move_info_list[id].typeId = 17;
        break;
    }
}

void set_type_info(int id)
{
    switch (id)
    {
    case 0:
        type_info_list[id].id = 0;
        type_info_list[id].typeName = "bug";
        break;
    case 1:
        type_info_list[id].id = 1;
        type_info_list[id].typeName = "dark";
        break;
    case 2:
        type_info_list[id].id = 2;
        type_info_list[id].typeName = "dragon";
        break;
    case 3:
        type_info_list[id].id = 3;
        type_info_list[id].typeName = "electric";
        break;
    case 4:
        type_info_list[id].id = 4;
        type_info_list[id].typeName = "fairy";
        break;
    case 5:
        type_info_list[id].id = 5;
        type_info_list[id].typeName = "fighting";
        break;
    case 6:
        type_info_list[id].id = 6;
        type_info_list[id].typeName = "fire";
        break;
    case 7:
        type_info_list[id].id = 7;
        type_info_list[id].typeName = "flying";
        break;
    case 8:
        type_info_list[id].id = 8;
        type_info_list[id].typeName = "ghost";
        break;
    case 9:
        type_info_list[id].id = 9;
        type_info_list[id].typeName = "grass";
        break;
    case 10:
        type_info_list[id].id = 10;
        type_info_list[id].typeName = "ground";
        break;
    case 11:
        type_info_list[id].id = 11;
        type_info_list[id].typeName = "ice";
        break;
    case 12:
        type_info_list[id].id = 12;
        type_info_list[id].typeName = "normal";
        break;
    case 13:
        type_info_list[id].id = 13;
        type_info_list[id].typeName = "poison";
        break;
    case 14:
        type_info_list[id].id = 14;
        type_info_list[id].typeName = "psychic";
        break;
    case 15:
        type_info_list[id].id = 15;
        type_info_list[id].typeName = "rock";
        break;
    case 16:
        type_info_list[id].id = 16;
        type_info_list[id].typeName = "steel";
        break;
    case 17:
        type_info_list[id].id = 17;
        type_info_list[id].typeName = "water";
        break;
    }
}

void initialize_pokemon_info_list()
{
    for (int i = 0; i < NUM_POKEMON; ++i)
    {
        set_pokemon_info(i);
    }
}

void initialize_move_info_list()
{
    for (int i = 0; i < NUM_MOVES; ++i)
    {
        set_move_info(i);
    }
}

void initialize_type_info_list()
{
    for (int i = 0; i < NUM_TYPES; ++i)
    {
        set_type_info(i);
    }
}

void initialize_data() {
    initialize_pokemon_info_list();
    initialize_move_info_list();
    initialize_type_info_list();
}