#include <iostream>
#include "enums.h"

class WorldElement {
    public:
        const virtual Action* getActions() = 0;
        virtual double getActionProbability(Action action) = 0;
    private:
        Action actions[] {};
};