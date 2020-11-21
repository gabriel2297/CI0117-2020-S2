#include <iostream>
#include "../include/WorldElement.h"
#include "../include/enums.h"
#define NO_JUMP 0.10
#define JUMP_AND_KILL 0.37
#define JUMP_AND_MOVE 0.53
#define TOTAL_ACTIONS 3

using namespace std;

class KoopaTroopa: public WorldElement {
    private:
        Action actions[TOTAL_ACTIONS] { no_jump, jump_and_kill, jump_and_move };
    public:
        const Action* getActions()
        {
            return actions;
        }
        double getActionProbability(Action action)
        {
            switch(action)
            {
                case no_jump:
                    return NO_JUMP;
                case jump_and_kill:
                    return JUMP_AND_KILL;
                case jump_and_move:
                    return JUMP_AND_MOVE;
                default:
                    return -1;
            }
        }
};