#include "../include/Game.h"
#include "../include/World.h"
#include "../include/WorldElement.h"
#include "../include/Player.h"
#include "../include/enums.h"
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

void Game::startGame(int argc, char* argv[])
{
    cout << "Argc = " << argc << ". Argv[1] = " << stoi(argv[1]) << ". Argv[2] = " << argv[2]  << endl;
    int position, player_id, playersActiveG, playersActiveL;
    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &this->num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this->my_pid);


    if(this->my_pid == 0)
    {
        this->picked_mario = atoi(argv[1]);
        if(this->picked_mario > num_processes){
            cout << "El id del Mario elegido no existe" << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        this->picked_strategy = getStrategyByLetter(argv[2]);
        cout << "Mario elegido: " << this->picked_mario << ". Estrategia = " << getStrategyAsString(this->picked_strategy) << ". Total de procesos: " << this->num_processes << endl;
    }
    
    // esperar a que el proceso 0 verifique los datos (antes de empezar el juego)
    MPI_Barrier(MPI_COMM_WORLD);

    if(this->my_pid != 0)
    {
        World *world = new World();
        cout << "Proceso " << this->my_pid << " dice: World creado de manera exitosa. "; 
        cout << "Elementos en posicion 9: " << world->getTotalElementsInPosition(9) << endl;
        delete world;
    }
    MPI_Finalize();

}