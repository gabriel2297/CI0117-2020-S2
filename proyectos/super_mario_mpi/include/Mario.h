#ifndef _MARIO
#define _MARIO
#include "enums.h"
#include <cstdlib>
#include <ctime>
#include "./WorldElements/Coins.h"
#include "./WorldElements/Holes.h"
#include "./WorldElements/KoopaTroopas.h"
#include "./WorldElements/LittleGoombas.h"

class Mario {
    private:
        int mario_id;
        int picked_mario_id;
        Strategy picked_strategy;
        int location;
        int coins;
        bool alive;
        int action;
        Coins coins_object;
        Holes holes_object;
        KoopaTroopas koopa_object;
        LittleGoombas goombas_object;
    public:
        Mario(int);
        ~Mario();
        void setLocation(int);
        void setCoins();
        void setIsAlive(bool);
        void setPickedMario(int);
        void setStrategy(Strategy);
        Strategy getStrategy();
        int getMyId();
        int getLocation();
        int getCoins();
        bool isAlive();
        bool iAmPickedMario();
        int chooseAction(int);
        double generateRandomNumber();
        Action getActionForElement(Element element);
};
#endif
