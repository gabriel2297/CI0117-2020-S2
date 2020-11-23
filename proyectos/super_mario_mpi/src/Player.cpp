#include "../include/Mario.h"
#include "../include/Player.h"

Player::Player(){
    this->mario = new Mario();
    this->active = true;
}

Player::~Player(){}

void Player::setActive(bool active){
    this->active = active;
}

bool Player::isActive(){
    return this->active;
}