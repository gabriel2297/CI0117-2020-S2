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
        int location;
        int coins;
        bool alive;
        int action;
        Coins *coins_object;
        Holes *holes_object;
        KoopaTroopas *koopa_object;
        LittleGoombas *goombas_object;
    public:
        Mario();
        ~Mario();
        void setLocation(int);
        void setCoins();
        void setIsAlive(bool);
        int getLocation();
        int getCoins();
        bool isAlive();
        int chooseAction(int);
        double generateRandomNumber(int);
        Action getActionForElement(Element element, int);
};
#endif
