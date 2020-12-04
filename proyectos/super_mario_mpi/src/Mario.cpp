#include "../include/Mario.h"

using namespace std;

Mario::Mario(int pid){
    this->action = 0;
    this->alive = true;
    this->coins = 0;
    this->location = 0;
    this->mario_id = pid;
    setMarioWithLessCoins(1, 99999);
    setMarioWithMoreCoins(1, 0);
}

Mario::~Mario(){}

void Mario::setStrategy(Strategy strategy)
{
    this->picked_strategy = strategy;
}

Strategy Mario::getStrategy()
{
    return this->picked_strategy;
}

void Mario::setMarioWithLessCoins(int process, int total_coins)
{
    this->mario_with_less_coins = process;
    this->total_less_coins = total_coins;
}

int Mario::getMarioWithLessCoins()
{
    return this->mario_with_less_coins;
}

void Mario::setMarioWithMoreCoins(int process, int total_coins)
{
    this->mario_with_more_coins = process;
    this->total_more_coins = total_coins;
}

int Mario::getMarioWithMoreCoins()
{
    return this->mario_with_more_coins;
}

int Mario::getTotalLessCoins()
{
    return this->total_less_coins;
}

int Mario::getTotalMoreCoins()
{
    return this->total_more_coins;
}

void Mario::setPickedMario(int id)
{
    this->picked_mario_id = id;
}

bool Mario::iAmPickedMario()
{
    return (this->picked_mario_id == getMyId()) ? true : false;
}

void Mario::setLocation(int location)
{
    this->location = location;
}

int Mario::getMyId()
{
    return this->mario_id;
}

void Mario::setIsAlive(bool alive){
    this->alive = alive;
}

void Mario::setCoins(){
    this->coins++;
}

int Mario::getLocation(){
    return this->location;
}

bool Mario::isAlive(){
    return this->alive;
}

int Mario::getCoins(){
    return this->coins;
}

Action Mario::getActionForElement(Element element)
{
    int limit = 100;
    double random_number = generateRandomNumber(limit);
    switch (element)
    {
        case Coin:
            return coins_object.getActionBasedOnProbability(random_number);
        case Hole:
            return holes_object.getActionBasedOnProbability(random_number);
        case LittleGoomba:
            return goombas_object.getActionBasedOnProbability(random_number);
        case KoopaTroopa:
            return koopa_object.getActionBasedOnProbability(random_number);
        default:
            cout << "An error ocurred at getActionForElement() in Mario" << endl;
            return no_action;
    }
}

double Mario::generateRandomNumber(int limit)
{
    srand((unsigned) time(NULL) * getMyId() * 1000);
    return (rand() % limit) + 1;
}

void Mario::generateRandomStrategy(){
    int limit = 100;
    srand((unsigned) time(NULL) * getMyId() * 1000);
    double random_number = generateRandomNumber(limit);
    if(random_number >= 75)
        this->setStrategy(random_strategy);
    else if (random_number >= 50 && random_number < 75)
        this->setStrategy(less_coins);
    else if (random_number >= 25 && random_number < 50)
        this->setStrategy(more_coins);
    else 
        this->setStrategy(attacker);
}

void Mario::chooseEnemy(int limit, int attacked_by)
{
    Strategy strategy = getStrategy();
    int random_enemy_picker = generateRandomNumber(limit);
    switch(strategy)
    {
        case less_coins:
            setEnemy(getMarioWithLessCoins());
            break;
        case more_coins:
            setEnemy(getMarioWithMoreCoins());
            break;
        case random_strategy:
            while(random_enemy_picker == getMyId() || random_enemy_picker == 0)
                random_enemy_picker = generateRandomNumber(limit);
            setEnemy(random_enemy_picker);
            break;
        case attacker:
            if(attacked_by == 0){
                while(random_enemy_picker == getMyId() || random_enemy_picker == 0)
                    setEnemy(random_enemy_picker);
            }
            else
                setEnemy(attacked_by);
            break;
        default:
            cout << "Error en chooseEnemy()" << endl;
            break;
    }
}

void Mario::setEnemy(int enemy_id)
{
    this->chosen_enemy = enemy_id;
}

int Mario::getEnemy()
{
    return this->chosen_enemy;
}