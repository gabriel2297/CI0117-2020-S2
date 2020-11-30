#include "../include/Game.h"
#include "../include/World.h"
#include "../include/WorldElement.h"
#include "../include/Player.h"
#include "../include/enums.h"
#include <unistd.h>
#include "mpi.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(){}
Game::~Game(){}

void Game::pickMario(int* picked_mario, int* total_processes)
{
    cout << "Elija el mario a seguir. Posibilidades: \n";
    for(int i = 0; i < *total_processes; ++i)
    {
        cout << "\t" << (i+1) << ") Mario " << (i+1) << "\n";
    }
    cout << "Su eleccion: ";
    cin >> *picked_mario;
    cout << endl;
}

void Game::pickStrategy(Strategy* picked_strategy)
{
    cout << "Elija la estrategia a utilizar. Posibilidades: \n";
    int eleccion = 0;
    string strategies[TOTAL_STRATEGIES] = {"random", "less_coins", "more_coins", "attacker"};
    for(int i = 0; i < TOTAL_STRATEGIES; ++i)
    {
        cout << "\t" << (i+1) << ") " << strategies[i] << "\n";
    }
    cout << "Su eleccion: ";
    cin >> eleccion;
    *picked_strategy = getStrategyByNumber(eleccion);
    cout << endl;
}

/**
 * Validates that the data passed via terminal is valid
 * @param argc pointer to int, number of arguments from terminal
 * @param argv char pointer, arguments from terminal
 * @return only returns true if everything passed. The program stops completely should it fail.
*/
bool Game::userInputIsValid(int* argc, char* argv[])
{
    if(*argc < 2)
    {
        cout << "Error, invalid number of parameters" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    this->picked_mario = atoi(argv[1]);

    if(this->picked_mario > this->num_processes || this->picked_mario <= 0){
        cout << "El id del Mario elegido no existe" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    this->picked_strategy = getStrategyByLetter(argv[2]);

    while(this->picked_strategy == none)
    {
        cout << "La estrategia que eligio para el mario " << this->picked_mario << " es invalida." << endl;
        pickStrategy(&this->picked_strategy);
    }

    return true;
}

/**
 * Starts the game with the arguments passed via terminal.
 * Takes care of all MPI related processes
*/
void Game::startGame(int argc, char* argv[])
{

    int position, player_id, playersActiveG, playersActiveL;
    MPI_Status status;
    MPI_Request request;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &this->num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this->my_pid);

    if(this->my_pid == 0 && userInputIsValid(&argc, argv))
        cout << "Mario elegido: " << this->picked_mario << ". Estrategia = " << getStrategyAsString(this->picked_strategy) << ". Total de procesos: " << this->num_processes << endl;
    
    // esperar a que el proceso 0 verifique los datos (antes de empezar el juego)
    MPI_Barrier(MPI_COMM_WORLD);
    
    //Se envia el id del mario escogido 
    MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_pid == 0){
        if (marioIsDead){
            cout << "Select another mario: ";
            cin >> picked_mario;
            MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    if(this->my_pid != 0)
    {
        World * world = new World();
        Player * player = new Player();
        int elements_in_position = 0;
        int marioIsDead = 0;
        Element the_element;
        Action action;
        while (playersActiveG > 1){
            for (int i = 0; i < WORLD_SLOTS; ++i){
                player->mario->setLocation(i);
                elements_in_position = world->getTotalElementsInPosition(player->mario->getLocation());
                if(elements_in_position > 0)
                {
                    if (my_pid == picked_mario){
                        cout << "Process " << this->my_pid << ". Elements at position: " << i << " " << world->getTotalElementsInPosition(i) << endl;
                    }
                    for(int element = 0; element < elements_in_position; element++)
                    {
                        the_element = world->getNextElementInPosition(player->mario->getLocation());
                        action = player->mario->getActionForElement(the_element);
                    }
                }
                MPI_Send(&marioIsDead, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);

                usleep(100000);
                if (i == WORLD_SLOTS - 1){
                    i = 0;
                }
            }
        }
        delete world;
        delete player;
    }
    MPI_Finalize();

}