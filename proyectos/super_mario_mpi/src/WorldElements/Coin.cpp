#include <iostream>
#include "../../include/WorldElement.h"
#include "../../include/enums.h"
#define NO_JUMP 0.5
#define JUMP_AND_HIT 0.5
#define TOTAL_ACTIONS 2

using namespace std;

class Coin : public WorldElement
{
private:
    Action actions[TOTAL_ACTIONS]{no_jump, jump_and_hit};

public:
    const Action *getActions()
    {
        return actions;
    }
    double getActionProbability(Action action)
    {
        switch (action)
        {
        case no_jump:
            return NO_JUMP;
        case jump_and_hit:
            return JUMP_AND_HIT;
        default:
            return -3;
        }
    }
};