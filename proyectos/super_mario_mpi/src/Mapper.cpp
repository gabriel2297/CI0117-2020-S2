#include "../include/Mapper.h"

using namespace std;

Mapper::Mapper(){}
Mapper::~Mapper(){}

void Mapper::setElementsAtIndex(World * world, int index){
  switch (index) {
        case 3:
            world->pushElement(LittleGoomba, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(Coin, index);
            world->pushElement(Coin, index);
        case 9:
            world->pushElement(Coin, index);
            world->pushElement(LittleGoomba, index);
            world->pushElement(LittleGoomba, index);
            break;
        case 12:
            world->pushElement(KoopaTroopa, index);
            world->pushElement(Coin, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(Coin, index);
            break;
    case 21:
            world->pushElement(LittleGoomba, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(LittleGoomba, index);
            break;
    case 26:
            world->pushElement(LittleGoomba, index);
            break;
    case 27:
            world->pushElement(LittleGoomba, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            break;
    case 35:
            world->pushElement(Hole, index);
            break;
    case 36:
            world->pushElement(Hole, index);
            break;
    case 40:
            world->pushElement(Coin, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            world->pushElement(KoopaTroopa, index);
            break;
    case 41:
            world->pushElement(LittleGoomba, index);
            break;
    case 42:
            world->pushElement(LittleGoomba, index);
            break;
    case 44:
            world->pushElement(Hole, index);
            break;
    case 45:
            world->pushElement(Hole, index);
            break;
    case 49:
            world->pushElement(Coin, index);
            world->pushElement(Coin, index);
            break;
    case 50:
            world->pushElement(LittleGoomba, index);
            break;
    case 51:
            world->pushElement(LittleGoomba, index);
            break;
    case 52:
            world->pushElement(Coin, index);
            break;
    case 55:
            world->pushElement(Coin, index);
            world->pushElement(KoopaTroopa, index);
            break;
    case 56:
            world->pushElement(Coin, index);
            world->pushElement(Coin, index);
            break;
    case 58:
            world->pushElement(Coin, index);
            break;
    case 59:
            world->pushElement(LittleGoomba, index);
            world->pushElement(LittleGoomba, index);
            break;
    case 65:
            world->pushElement(LittleGoomba, index);
            world->pushElement(LittleGoomba, index);
            break;
    case 67:
            world->pushElement(LittleGoomba, index);
            world->pushElement(Coin, index);
            break;
    case 68:
            world->pushElement(LittleGoomba, index);
            world->pushElement(Coin, index);
            break;
    case 80:
            world->pushElement(Hole, index);
            break;
    case 81:
            world->pushElement(Hole, index);
            break;
    case 89:
            world->pushElement(Coin, index);
            break;
    case 91:
            world->pushElement(LittleGoomba, index);
            break;
    case 92:
            world->pushElement(LittleGoomba, index);
            break;
    case 103:
            world->pushElement(Flag, index);
            break;
    default:
            break;
  }
}
