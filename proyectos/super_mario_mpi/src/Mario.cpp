#include "../include/Mario.h"

using namespace std;

Mario::Mario(){
    this->action = 0;
    this->alive = true;
    this->coins = 0;
    this->location = 0;
    this->coins_object = new Coins();
    this->holes_object = new Holes();
    this->koopa_object = new KoopaTroopas();
    this->goombas_object = new LittleGoombas();
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
    cout << "random_number = " << random_number << endl;
    switch (element)
    {
        case Coin:
            return coins_object->getActionBasedOnProbability(random_number);
        case Hole:
            return holes_object->getActionBasedOnProbability(random_number);
        case LittleGoomba:
            return goombas_object->getActionBasedOnProbability(random_number);
        case KoopaTroopa:
            return koopa_object->getActionBasedOnProbability(random_number);
        default:
            cout << "An error ocurred at getActionForElement() in Mario" << endl;
            return no_action;
    }
}

double Mario::generateRandomNumber()
{
    srand((unsigned) time(0));
    return (rand() % 100) + 1;
}