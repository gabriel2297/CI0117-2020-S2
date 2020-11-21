#include "../include/Mario.h"

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

