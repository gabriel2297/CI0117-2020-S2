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
        double start_time, end_time;
        int mario_is_alive;
        Strategy picked_strategy;
        Element the_element;
        Action action;
        World *world;
        Mario *mario;
        bool userInputIsValid(int* argc, char* argv[]);

    public:
        void pickMario();
        void pickStrategy(Strategy* picked_strategy);
        void setProcessesAlive();
        int getChosenMario();
        void startGame(int argc, char* argv[]);
        int getProcessesAlive();
        void printAliveProcesses();
        void movePositions();
        Game();
        ~Game();
};