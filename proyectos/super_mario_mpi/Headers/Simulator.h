#ifndef _SIMULATOR
#define _SIMULATOR
#include "mpi.h"
#include "World.h"
#define LENGTH 150

class Simulator {
  private:
    World * world;
    int attack;
  public:
    Simulator();
    ~Simulator();
    void run(int, char *);
    
};
#endif
