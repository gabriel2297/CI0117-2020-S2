#ifndef GOOMBA_H
#define GOOMBA_H

#include <iostream>
#include "../WorldElement.h"

class LittleGoombas : public WorldElement
{
    private:
        double NO_JUMP = 0.5;
        double JUMP_AND_KILL = 0.40;
        double JUMP_AND_MOVE = 0.55;
    public:
        LittleGoombas(){}
        Action getActionBasedOnProbability(double probability)
        {
            if(probability <= (NO_JUMP*100))
                return no_jump;
            else if (probability < (JUMP_AND_MOVE * 100))
                return jump_and_kill;
            else 
                return jump_and_move;
        }
};

#endif