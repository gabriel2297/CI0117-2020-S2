#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <queue>
#include <vector>
#include "enums.h"

#define WORLD_SLOTS 103

class World
{
private:
  std::vector<std::queue<Element>> world;
  typedef std::queue<Element> cola;
  void initWorld();

public:
  World();
  ~World();
  void pushElement(Element, int);
  int World::getTotalElementsInPosition(int index);
  Element getNextElementInPosition(int);
};

#endif
