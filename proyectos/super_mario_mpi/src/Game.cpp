#include "../include/Game.h"
#include "../include/WorldElement.h"
#include <unistd.h>
#include "mpi.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(){
    this->mario_is_alive = 1;
}
Game::~Game(){}

/**
 * @return the id of the mario picked by the user
*/
int Game::getChosenMario()
{
    return this->picked_mario;
}

/**
 * Requests a mario to be chosen by the user
 * @param picked_mario pointer to the pid of the mario the user chose
*/
void Game::pickMario()
{
    cout << "\nElija el nuevo mario a seguir. Posibilidades: \n";
    for(int i = 1; i < this->num_processes; ++i)
    {
        if(this->processes_alive[i] == 1){
            cout << "\t" << i << ") Mario " << i << "\n";
        }
    }
    cout << "Su eleccion: ";
    cin >> this->picked_mario;
    cout << endl;
}

/**
 * Requests the chosen Mario for the strategy it picked. 
 * @param picked_strategy pointer to the stategy that the game will use
*/
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

    if(getChosenMario() > this->num_processes || getChosenMario() <= 0){
        cout << "El id del Mario elegido no existe" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    this->picked_strategy = getStrategyByLetter(argv[2]);

    while(this->picked_strategy == none)
    {
        cout << "La estrategia que eligio para el mario " << getChosenMario() << " es invalida." << endl;
        pickStrategy(&this->picked_strategy);
    }

    return true;
}

/**
 * @return total processes alive 
*/
int Game::getProcessesAlive()
{   
    int counter = 0;
    for(int i = 0; i < this->num_processes; ++i)
    {
        if(this->processes_alive[i] == 1)
            counter++;
    }
    return counter;
}

/**
 * Sets all processes in the game as alive
*/
void Game::setProcessesAlive()
{
    for(int i = 0; i < this->num_processes; ++i)
        this->processes_alive[i] = 1;
}

/**
 * Helper method to know which processes are still alive.
 * Prints 1 if alive, 0 if dead
*/
void Game::printAliveProcesses()
{
    for(int i = 0; i < this->num_processes; ++i)
    {
        cout << "Process " << i << " is " << this->processes_alive[i] << endl;
    }
}

/**
 * Metodo que se llama cada vez que Mario avanza de posicion
*/
void Game::movePositions()
{
    if(mario->isAlive())
    {
        if(mario->iAmPickedMario())
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << " is walking." << endl;

        // obtener los elementos en la posicion en la que mario esta
        int elements_in_position = world->getTotalElementsInPosition(mario->getLocation());

        // mientras hayan elementos...
        while(elements_in_position > 0)
        {
            // obtener el elemento y hacer algo con el
            the_element = world->getNextElementInPosition(mario->getLocation());
            action = mario->getActionForElement(the_element);
            switch(action)
            {
                case no_jump:
                    if (mario->iAmPickedMario())
                        cout << "Mario " << mario->getMyId() << ": " << getActionAsString(action) << endl;
                    if(the_element != Coin){
                        mario->setIsAlive(false);
                        this->mario_is_alive = mario->isAlive();
                    }
                    break;
                case jump_and_hit:
                    mario->setCoins();
                    if (mario->iAmPickedMario())
                        cout << getActionAsString(action) << " Total coins: "  << mario->getCoins() << endl;
                    break;
                case jump_and_kill:
                    if (mario->iAmPickedMario())
                        cout << "Mario " << my_pid << ": " << getActionAsString(action) << getElementAsString(the_element) << endl;
                    break;
                case jump_and_move:
                    if (mario->iAmPickedMario())
                        cout << "Mario " << my_pid << ": " << getActionAsString(action) << endl;
                    break;
                case no_action:
                    break;
            }
        }
    }
}

/**
 * Starts the game with the arguments passed via terminal.
 * Takes care of all MPI related processes
*/
void Game::startGame(int argc, char* argv[])
{
    // inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &this->num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &this->my_pid);

    // crear las variables a utilizar e instanciar objetos
    int coins[this->num_processes];
    this->processes_alive = new int[this->num_processes];
    world = new World();
    mario = new Mario(this->my_pid);
    setProcessesAlive();

    // validar la informacion del usuario e imprimir la informacion de lo elegido
    if(mario->getMyId() == 0 && userInputIsValid(&argc, argv))
        cout << "Mario elegido: " << getChosenMario() << ". Estrategia: " << getStrategyAsString(this->picked_strategy) << ". Total de procesos: " << (this->num_processes - 1)<< endl;

    // si el proceso != 0: esperar a que el 0 verifique los datos
    MPI_Barrier(MPI_COMM_WORLD);

    // Se envia el id del mario escogido
    MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Asigno el mario que es el elegido para imprimir
    mario->setPickedMario(picked_mario);

    // Se envia un arreglo de enteros donde cada proceso almacena la cantidad de monedas que tiene al obtener una moneda
    MPI_Bcast(coins, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // mientras hayan posiciones en el mundo y la cantidad de procesos sea mayor a 2 (2 = el 0 y el ganador)
    int i = 0; 
    while(i < WORLD_SLOTS && getProcessesAlive() > 2)
    {
        // recorrer el mundo
        mario->setLocation(i);
        movePositions();
        
        // reportar a todos los otros procesos mi estado
        MPI_Allgather(&this->mario_is_alive, 1, MPI_INT, processes_alive, 1, MPI_INT, MPI_COMM_WORLD);

        /* Esperar a que el proceso cero termine de validar los datos */
        if (mario->getMyId() == 0 && processes_alive[getChosenMario()] == 0 && getProcessesAlive() > 2)
            pickMario();
        
        // decirle a todos los procesos quien es el mario elegido
        MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);
        mario->setPickedMario(picked_mario);
        MPI_Barrier(MPI_COMM_WORLD);
        
        // dormir unos segundos para poder ver la ejecucion
        usleep(1000000);
        if (i == WORLD_SLOTS - 1){
            i = 0;
        }
        
        ++i;
    }
    
    for (int i = 0; i < num_processes; ++i){
        if (i != 0 && processes_alive[i] != 0 && mario->getMyId() == i){
            cout << "El Ganador es el: " << i << endl;
        }
    }

    MPI_Finalize();
    delete world;
    delete mario;
}
