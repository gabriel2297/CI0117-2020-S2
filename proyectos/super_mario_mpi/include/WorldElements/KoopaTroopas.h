#ifndef KOOPA_H
#define KOOPA_H
#include <iostream>
#include "../WorldElement.h"

class KoopaTroopas : public WorldElement
{
    private:
         double NO_JUMP = 0.10;
         double JUMP_AND_KILL = 0.37;
         double JUMP_AND_MOVE = 0.53;
    public:
        KoopaTroopas(){}
        Action getActionBasedOnProbability(double probability)
        {
        if(probability <= (NO_JUMP*100))
            return no_jump;
        else if(probability < (JUMP_AND_MOVE*100))
            return jump_and_kill;
        else
            return jump_and_move;
        }
};

#endif