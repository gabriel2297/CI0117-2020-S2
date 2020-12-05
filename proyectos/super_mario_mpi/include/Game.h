#pragma once
#define GAME_H
#include "enums.h"
#include "World.h"
#include "Mario.h"
#include <list>

#define TOTAL_STRATEGIES 4

class Game
{
    private:
        int picked_mario;
        int num_processes;
        int my_pid;
        int chosen_enemy;
        int * processes_alive;
        int * coins_per_process;
        int * koopas_per_process;
        int * goombas_per_process;
        int * attacking_processes;
        int * strategy_per_process;
        double start_time, end_time;
        int mario_is_alive;
        int total_coins;
        int mario_less_coins;
        int mario_more_coins;
        int koopas;
        int goombas;
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
        void computeCoinsPerMario();
        void initStructuresPerProcess();
        void printEnemiesKilled();
        bool isProcessAlive(int pid);
        void printAllStrategies();
        void computeAttackerPerMario();
    public:
        void startGame(int argc, char* argv[]);
        Game();
        ~Game();
};