#include "../include/Mario.h"

using namespace std;

Mario::Mario(int pid){
    this->action = 0;
    this->alive = true;
    this->coins = 0;
    this->location = 0;
    this->mario_id = pid;
}

Mario::~Mario(){}

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
    double random_number = generateRandomNumber();
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

double Mario::generateRandomNumber()
{
    srand((unsigned) time(NULL) * getMyId() * 1000);
    return (rand() % 100) + 1;
}