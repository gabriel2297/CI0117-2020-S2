#ifndef _MARIO
#define _MARIO
#include "enums.h"
#include <cstdlib>
#include <ctime>
#include "./WorldElements/Coins.h"
#include "./WorldElements/Holes.h"
#include "./WorldElements/KoopaTroopas.h"
#include "./WorldElements/LittleGoombas.h"
#include <vector>

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
        int koopas_count;
        int goombas_count;
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
        void setKoopas();
        void setGoombas();
        Strategy getStrategy();
        int getMyId();
        int getLocation();
        int getCoins();
        bool isAlive();
        bool iAmPickedMario();
        int chooseAction(int);
        int getMarioWithLessCoins();
        int getMarioWithMoreCoins();
        void setMarioWithLessCoins(int);
        void setMarioWithMoreCoins(int);
        double generateRandomNumber(int, int);
        Action getActionForElement(Element element);
        double generateRandomNumberFromArray(std::vector<int> *the_vector, int pid);
        void generateRandomStrategy();
        void chooseEnemy(int, int);
        int getEnemy();
        int getKoopas();
        int getGoombas();
        void setEnemy(int);
};
#endif
