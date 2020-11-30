#ifndef _MARIO 
#define _MARIO
#include "enums.h"
#include <cstdlib>
#include <ctime>

class Mario {
    private:
        int location;
        int coins;
        bool alive;
        int action;
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
        void performActionOnElement(Element element);
        double generateRandomNumber();
        Action getActionForElement(Element element);
};
#endif
