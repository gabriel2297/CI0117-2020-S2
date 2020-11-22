#ifndef WORLD_ELEMENT_H
#define WORLD_ELEMENT_H
#include <iostream>
#include "enums.h"

class WorldElement
{
private:
    Action actions[]{};

public:
    const virtual Action *getActions() = 0;
    virtual double getActionProbability(Action action) = 0;
};

#endif