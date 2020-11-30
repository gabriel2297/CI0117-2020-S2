#include "include/Game.h"
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
  // validaciones se realizan dentro del game en si
  Game game;
  game.startGame(argc, argv);
  return 0;
}
