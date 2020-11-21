#include <iostream>
#include "../include/WorldElement.h"
#include "../include/enums.h"
#define NO_JUMP 0.05
#define JUMP_AND_KILL 0.40
#define JUMP_AND_MOVE 0.53
#define TOTAL_ACTIONS 3

using namespace std;

class LittleGoomba: public WorldElement {
    public:
        const Action* getActions()
        {
            return actions;
        }
        double getActionProbability(Action action)
        {
            switch(action){
                case no_jump:
                    return NO_JUMP;
                case jump_and_kill:
                    return JUMP_AND_KILL;
                case jump_and_move:
                    return JUMP_AND_MOVE;
                default:
                    return -2;
            }
        }
    private:
        Action actions[TOTAL_ACTIONS] { no_jump, jump_and_kill, jump_and_move };
};