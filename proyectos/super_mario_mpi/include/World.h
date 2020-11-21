#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <queue>
#include <vector>
#include "enums.h"

#define WORLD_SLOTS 130

class World 
{
  private:
    std::vector<std::queue<Element>> world;
    typedef std::queue<Element> cola;
    void initWorld();
  public:
    World();
    ~World();
    void pushCoin(int);
    void pushHole(int);
    void pushLittleGoomba(int);
    void pushKoopaTroopa(int); 
    Element getTotalElementsInPosition(int);
    Element getNextElementInPosition(int);
};

#endif
