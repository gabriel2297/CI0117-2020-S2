#include "../include/Mario.h"
#include "WorldElements/Coin.cpp"

Mario::Mario(){
    this->action = 0;
    this->alive = true;
    this->coins = 0;
    this->location = 0;
}

Mario::~Mario(){
    delete this;
}

void Mario::setLocation(int location){
    this->location = location;
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
    Coin coin;
    switch (element)
    {
        case Coin:
            return coin.getActionBasedOnProbability(random_number);
        case Hole:
            break;
        case LittleGoomba:
            break;
        case KoopaTroopa:
            break;
        default:
            break;
    }
}

double Mario::generateRandomNumber()
{
    srand((unsigned) time(0));
    return (rand() % 100) + 1;
}