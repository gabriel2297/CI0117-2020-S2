#ifndef WORLD_ELEMENT_H
#define WORLD_ELEMENT_H
#include <iostream>
#include "enums.h"

class WorldElement
{
    private:
        double NO_JUMP;
        double JUMP_AND_KILL;
        double JUMP_AND_MOVE;
    public:
        virtual Action getActionBasedOnProbability(double probability) = 0;
};

#endif