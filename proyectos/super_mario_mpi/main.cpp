#include "include/Game.h"
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
  if (argc > 2){
    Game game;
    game.startGame(argc, argv);

  } else {
    cout << "Error, invalid number of parameters" << endl;
    return 1;
  }
  return 0;
}
