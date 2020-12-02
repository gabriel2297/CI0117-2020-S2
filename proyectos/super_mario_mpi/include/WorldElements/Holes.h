#ifndef HOLES_H
#define HOLES_H
#include <iostream>
#include "../WorldElement.h"

class Holes : public WorldElement
{
    private:
         double NO_JUMP = 0.5;
         double JUMP_AND_MOVE = 0.95;
    public:
        Holes(){}
        Action getActionBasedOnProbability(double probability)
        {
            if(probability < (NO_JUMP*100))
                return no_jump;
            else
                return jump_and_move;
        }
};

#endif 