#include "../include/Game.h"
#include "../include/World.h"
#include "../include/WorldElement.h"
#include "../include/Player.h"
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

    //int position, player_id, playersActiveL;
    // MPI_Status status;
    // MPI_Request request;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &this->num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this->my_pid);

    int playersActiveG = num_processes - 1;
    int playersActiveL = 1;
    if(this->my_pid == 0 && userInputIsValid(&argc, argv)){
        cout << "Mario elegido: " << this->picked_mario << ". Estrategia = " << getStrategyAsString(this->picked_strategy) << ". Total de procesos: " << this->num_processes << endl;
    }
    // esperar a que el proceso 0 verifique los datos (antes de empezar el juego)
    MPI_Barrier(MPI_COMM_WORLD);

    //Se envia el id del mario escogido
    MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int marioIsDead = 0;
    if (my_pid == 0){
        if (marioIsDead){
            cout << "Select another mario: ";
            cin >> picked_mario;
            MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }
    }

    World * world = new World();
    Mario * mario = new Mario();
    int * coins = new int[this->num_processes];
    int elements_in_position = 0;

    Element the_element;
    Action action;

    //Se envia un arreglo de enteros donde cada proceso almacena la cantidad de monedas que tiene al obtener una moneda
    MPI_Bcast(coins, 1, MPI_INT, 0, MPI_COMM_WORLD);
    while (playersActiveG > 1) {
        for (int i = 0; i < WORLD_SLOTS; ++i){
            mario->setLocation(i);
            elements_in_position = world->getTotalElementsInPosition(mario->getLocation());
            if (my_pid == picked_mario)
                cout << "Mario " << my_pid << " is walking." << endl;
            if(elements_in_position > 0)
            {
                for(int element = 0; element < elements_in_position; element++)
                {
                    the_element = world->getNextElementInPosition(mario->getLocation());
                    action = mario->getActionForElement(the_element, my_pid);
                    /* En cualquiera de las acciones que involucre que mario muere hay que restar a la cantidad de jugadores activos */
                    if(my_pid == 0)
                        cout << "Players active = " << playersActiveG << endl;
                    switch(action)
                    {
                        case no_jump:
                            if(the_element != Coin){
                                mario->setIsAlive(false);
                                if(my_pid == picked_mario)
                                {
                                    picked_mario = -1;
                                    cout << "proc " << my_pid << " picked_mario = " << picked_mario << endl;
                                    MPI_Bcast(&picked_mario, 1, MPI_INT, my_pid, MPI_COMM_WORLD);
                                    cout << " proc " << my_pid << " murio, notificando a los demas " << endl;
                                }
                                playersActiveL = 0;
                                cout << "Mario " << my_pid << " died" << endl;
                            }
                            if (my_pid == picked_mario)
                                cout << "Mario " << my_pid << ": " << getActionAsString(action) << endl;
                            break;
                        case jump_and_hit:
                            mario->setCoins();
                            if (my_pid == picked_mario)
                                cout << "Mario " << my_pid << ": " << getActionAsString(action) << " Total coins: "  << mario->getCoins() << endl;
                            break;
                        case jump_and_kill:
                            if (my_pid == picked_mario)
                                cout << "Mario " << my_pid << ": " << getActionAsString(action) << getElementAsString(the_element) << endl;
                            break;
                        case jump_and_move:
                            if (my_pid == picked_mario)
                                cout << "Mario " << my_pid << ": " << getActionAsString(action) << endl;
                            break;
                        case no_action:
                            break;
                    }
                }
            }

            if (picked_mario == -1)
            {
                /* Esperar a que el proceso cero termine de validar los datos */
                if (my_pid == 0){
                    cout << "El mario se murio" << endl;
                    cout << "Select the number of the mario: ";
                    cin >> picked_mario;
                }
                else
                {
                    cout << "proc " << my_pid << " esperando en el barrier...." << endl;
                }
                
                MPI_Barrier(MPI_COMM_WORLD);
            }

            usleep(1000000);
            MPI_Reduce(&playersActiveL, &playersActiveG, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
            if (i == WORLD_SLOTS - 1){
                i = 0;
            }
        }
        delete world;
        delete mario;
    }
    MPI_Finalize();

}
