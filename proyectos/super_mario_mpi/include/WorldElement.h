#ifndef WORLD_ELEMENT_H
#define WORLD_ELEMENT_H
#include <iostream>
#include "enums.h"

class WorldElement
{
    private:
        Action action;

    public:
        const virtual Action *getActions() = 0;
        virtual Action getActionBasedOnProbability(double probability) = 0;
};

#endif