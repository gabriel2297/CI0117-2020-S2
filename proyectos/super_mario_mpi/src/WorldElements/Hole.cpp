#include <iostream>
#include "../../include/WorldElement.h"
#include "../../include/enums.h"
#define NO_JUMP 0.5
#define JUMP_AND_MOVE 0.95
#define TOTAL_ACTIONS 2

using namespace std;

class Hole : public WorldElement
{
private:
    Action actions[TOTAL_ACTIONS]{no_jump, jump_and_move};

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
        case jump_and_move:
            return JUMP_AND_MOVE;
        default:
            return -4;
        }
    }
};
