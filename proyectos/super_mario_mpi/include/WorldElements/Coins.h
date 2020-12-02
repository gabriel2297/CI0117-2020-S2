#ifndef COINS_H
#define COINS_H
#include <iostream>
#include "../WorldElement.h"

class Coins : public WorldElement
{
    private:
         double NO_JUMP = 0.5;
         double JUMP_AND_HIT = 0.5;
    public:
        Coins(){}
        Action getActionBasedOnProbability(double probability)
        {
            if(probability < (NO_JUMP*100))
                return no_jump;
            else
                return jump_and_hit;
        }
};



#endif /* COINS_H */