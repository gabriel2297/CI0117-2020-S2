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
        Coin(){}
        ~Coin(){delete this;}
        Action getActionBasedOnProbability(double probability)
        {
            if(probability < (NO_JUMP*100))
                return no_jump;
            else
                return jump_and_hit;
        }
};