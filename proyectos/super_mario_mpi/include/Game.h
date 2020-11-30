#pragma once
#define GAME_H
#include "enums.h"

#define TOTAL_STRATEGIES 4

class Game
{
    private:
        int picked_mario;
        int num_processes;
        int my_pid;
        double start_time, end_time;
        Strategy picked_strategy;
        bool userInputIsValid(int* argc, char* argv[]);

    public:
        void pickMario(int* picked_mario, int* num_processes);
        void pickStrategy(Strategy* picked_strategy);
        void startGame(int argc, char* argv[]);
        Game();
        ~Game();
};