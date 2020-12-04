#include "../include/Game.h"
#include "../include/WorldElement.h"
#include <unistd.h>
#include "mpi.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(){
    this->mario_is_alive = 1;
    this->total_coins = 0;
    this->mario_less_coins = 9999999;
    this->mario_more_coins = 0;
    this->koopas = 0;
    this->goombas = 0;
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

void Game::distributeElementsForEnemy(Element element)
{
    switch(element)
    {
        case KoopaTroopa:
            this->koopas_received[mario->getEnemy()] = this->koopas;
            break;
        case LittleGoomba:
            this->goombas_received[mario->getEnemy()] = this->goombas;
            break;
        default:
            cout << "error en funcion distributeElementsForEnemy()" << endl;
             break;
    }
}

void Game::getElementsFromEnemies()
{
    int goombas_received = this->goombas_received[mario->getMyId()];
    int koopas_received = this->koopas_received[mario->getMyId()];
}

void Game::printMariosActionBasedOnElement(Action action, Element element)
{
    switch(element)
    {
        case KoopaTroopa:
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) <<  ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;
        case LittleGoomba:
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) << ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;
        case Coin:
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) << ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;
        default:
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) << ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;
    }
}

/**
 * Realizar una accion en un elemento, por cada posicion.
 * @param action - accion a realizar 
 * @param element - elemento sobre el cual realizamos la accion
*/
void Game::doActions(Action action, Element element)
{
    switch(action)
    {
        case no_jump:
            
            break;
        case jump_and_hit:
            mario->setCoins();
            ++this->total_coins;
            if (mario->iAmPickedMario())
                cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) <<  " Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;
        case jump_and_kill:
            if (element == KoopaTroopa)
            {
                this->koopas+=1;
                cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) << getElementAsString(element) <<  ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;            
                distributeElementsForEnemy(element);
                break;
            }
            else if (element == LittleGoomba)
            {
                this->goombas += 1;
                cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) << getElementAsString(element) <<  ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;            
                distributeElementsForEnemy(element);
                break;
            }
            else{
                break;
            }
        case jump_and_move:
            if (mario->iAmPickedMario())
                cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << getActionAsString(action) <<  ". Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()-1) << endl;
            break;

        case no_action:
            break;
    }
}

/**
*  Metodo que se llama cada vez que Mario avanza de posicion
*/
void Game::movePositions()
{
    if(mario->isAlive() && mario->getMyId() != 0)
    {
        // obtener los elementos en la posicion en la que mario esta
        int elements_in_position = world->getTotalElementsInPosition(mario->getLocation());
        while(elements_in_position > 0)
        {
            // obtener el elemento y la accion de ese elemento
            the_element = world->getNextElementInPosition(mario->getLocation());
            action = mario->getActionForElement(the_element);
            
            // realizar la accion, luego revisar si mario murio o no
            doActions(action, the_element);
            if(!mario->isAlive())
                break;

            // restarle 1 a la cantidad de elementos en la posicion 
            --elements_in_position;
        }
    }
}

void Game::printWinnerMario()
{
    for (int i = 0; i < this->num_processes; ++i)
    {
        if (processes_alive[i] == 1 && i != 0){
            cout << "El Ganador es Mario " << i << "!!!" << endl;
            break;
        }
    }
}

void Game::initCoinsPerProcess()
{
    for(int i = 0; i < this->num_processes; ++i)
        coins_per_process[i] = 0;
}

void Game::restartEnemiesPerProcessCounters()
{
    this->koopas = 0;
    this->goombas = 0;
}

void Game::initElementsSentByOthers()
{
    for(int i = 0; i < this->num_processes; ++i)
    {
        this->koopas_to_send[i] = 0;
        this->goombas_to_send[i] = 0;
        this->koopas_received[i] = 0;
        this->goombas_received[i] = 0;
    }
}

void Game::computeLessCoinsMario()
{
    for(int i = 0; i < this->num_processes; ++i)
    {
        if(coins_per_process[i] < mario->getTotalLessCoins() && i!=0)
            mario->setMarioWithLessCoins(i, coins_per_process[i]);
    }
}

void Game::computeMoreCoinsMario()
{
    for(int i = 0; i < this->num_processes; ++i)
    {
        if(coins_per_process[i] > mario->getTotalMoreCoins() && i!=0)
            mario->setMarioWithMoreCoins(i, coins_per_process[i]);
    }
}

void Game::computeReceivedElements()
{
    int index = mario->getMyId();
    int current_position = mario->getLocation();
    int add_to_position = ((current_position + 10) > WORLD_SLOTS) ? ((current_position+10) - WORLD_SLOTS) : (current_position+10);
    int total_koopas = this->koopas_received[index];
    int total_goombas = this->goombas_received[index];
    cout << "total_koopas " << total_koopas << " para mario " << mario->getMyId() << endl;
    cout << "total_goombas " << total_goombas << " para mario " << mario->getMyId() << endl;
    while(total_koopas > 0)
    {
        world->pushElement(KoopaTroopa, add_to_position);
        --total_koopas;
    }
    while(total_goombas > 0)
    {
        world->pushElement(LittleGoomba, add_to_position);
        --total_goombas;
    }
}

int Game::getBeingAttackedBy()
{
    int attacked_by_process = 1;
    for(int i = 0; i < this->num_processes; ++i)
    {
        if(this->attacking_processes[i] == this->my_pid && this->attacking_processes[i] != 0 && i != 0)
        {
            attacked_by_process = i;
            break;
        }
    }
    return attacked_by_process;
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
    this->coins_per_process = new int[this->num_processes];
    this->processes_alive = new int[this->num_processes];
    this->koopas_received = new int[this->num_processes];
    this->goombas_received = new int[this->num_processes];
    this->attacking_processes = new int[this->num_processes];
    this->koopas_to_send = new int[this->num_processes];
    this->goombas_to_send = new int[this->num_processes];

    world = new World();
    mario = new Mario(this->my_pid);
    setProcessesAlive();
    initCoinsPerProcess();
    initElementsSentByOthers();
    
    // validar la informacion del usuario e imprimir la informacion de lo elegido
    if(mario->getMyId() == 0 && userInputIsValid(&argc, argv))
        cout << "Mario elegido: " << getChosenMario() << ". Estrategia: " << getStrategyAsString(this->picked_strategy) << ". Total de procesos: " << (this->num_processes - 1)<< endl;

    // si el proceso != 0: esperar a que el 0 verifique los datos
    MPI_Barrier(MPI_COMM_WORLD);

    // Se envia el id del mario escogido y la estrategia
    MPI_Bcast(&picked_mario, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&picked_strategy, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Asigno el mario que es el elegido para imprimir y la estrategia elegida
    mario->setPickedMario(picked_mario);
    mario->setStrategy(picked_strategy);


    //Para los marios que no son el escogido se selecciona una estrategia al azar
    if ( mario->getMyId() != getChosenMario() && mario->getMyId() != 0){
        mario->generateRandomStrategy();
    }

    // Se envia un arreglo de enteros donde cada proceso almacena la cantidad de monedas que tiene al obtener una moneda
    MPI_Allgather(&this->total_coins, 1, MPI_INT, coins_per_process, 1, MPI_INT, MPI_COMM_WORLD);

    // mientras hayan posiciones en el mundo y la cantidad de procesos sea mayor a 2 (2 = el 0 y el ganador)
    int i = 0; 
    while(i < WORLD_SLOTS && getProcessesAlive() > 2)
    {
        computeLessCoinsMario();
        computeMoreCoinsMario();
        computeReceivedElements();

        // poner a quien vamos a atacar en base a la estrategia y a los calculos de arriba, comunicarselo a los demas
        if(i == 0)
            mario->chooseEnemy((this->num_processes), 0);
        else
            mario->chooseEnemy((this->num_processes), getBeingAttackedBy());
        chosen_enemy = mario->getEnemy();

        MPI_Allgather(&chosen_enemy, 1, MPI_INT, attacking_processes, 1, MPI_INT, MPI_COMM_WORLD);

        // actualizar la posicion de mario
        mario->setLocation(i);
        if(mario->iAmPickedMario())
        {
            cout << "World pos. " << mario->getLocation() << ". Mario " << mario->getMyId() << " is walking. Coins: " << mario->getCoins() \
                 << " | attacking #" << mario->getEnemy() << " | being attacked by " << getBeingAttackedBy() \
                 << " | Attack strategy: " << getStrategyAsString(this->picked_strategy) << ". Total playing: " << (getProcessesAlive()) << endl;
        }
        
        // recorrer el mundo
        movePositions();
        
        // reportar a todos los otros procesos mi estado y la cantidad de monedas
        MPI_Allgather(&this->mario_is_alive, 1, MPI_INT, processes_alive, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(&this->total_coins, 1, MPI_INT, coins_per_process, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(&this->goombas_to_send[mario->getEnemy()], 1, MPI_INT, goombas_received, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(&this->koopas_to_send[mario->getEnemy()], 1, MPI_INT, koopas_received, 1, MPI_INT, MPI_COMM_WORLD);
        restartEnemiesPerProcessCounters();
        
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

        // revisar si tengo que empujar algun enemigo
        ++i;
    }

    if(my_pid == 0)
        printWinnerMario();

    MPI_Finalize();
    delete world;
    delete mario;
}
