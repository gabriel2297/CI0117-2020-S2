#include <iostream>
#include "include/World.h"
#include "include/Mapper.h"
using namespace std;

int main (int argc, char * argv[])
{
  World *world = new World();
  cout << "elements in position 9: " << world->getTotalElementsInPosition(9) << endl;
  delete world;
  return 0;
}
