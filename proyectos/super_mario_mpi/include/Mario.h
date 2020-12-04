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
        int chosen_enemy;
        int mario_with_more_coins;
        int mario_with_less_coins;
        int total_less_coins;
        int total_more_coins;
        Strategy picked_strategy;
        int location;
        int coins;
        bool alive;
        int action;
        Coins coins_object;
        Holes holes_object;
        KoopaTroopas koopa_object;
        LittleGoombas goombas_object;
        void setEnemy(int);

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
        int getMarioWithLessCoins();
        int getMarioWithMoreCoins();
        int getTotalLessCoins();
        int getTotalMoreCoins();
        void setMarioWithLessCoins(int, int);
        void setMarioWithMoreCoins(int, int);
        double generateRandomNumber(int);
        Action getActionForElement(Element element);
        void generateRandomStrategy();
        void chooseEnemy(int, int);
        int getEnemy();
};
#endif
