#pragma once
#define GAME_H
#include "enums.h"
#include "World.h"
#include "Mario.h"

#define TOTAL_STRATEGIES 4

class Game
{
    private:
        int picked_mario;
        int num_processes;
        int my_pid;
        int * processes_alive;
        int * coins_per_process;
        double start_time, end_time;
        int mario_is_alive;
        int total_coins;
        int mario_less_coins;
        int mario_more_coins;
        Strategy picked_strategy;
        Element the_element;
        Action action;
        World *world;
        Mario *mario;
        bool userInputIsValid(int* argc, char* argv[]);
        void doActions(Action, Element);
        void pickMario();
        void pickStrategy(Strategy* picked_strategy);
        void setProcessesAlive();
        int getChosenMario();
        int getProcessesAlive();
        void printAliveProcesses();
        void movePositions();
        void printWinnerMario();
        void computeLessCoinsMario();
        void computeMoreCoinsMario();
        void setCoinsPerProcess();
    public:
        void startGame(int argc, char* argv[]);
        Game();
        ~Game();
};