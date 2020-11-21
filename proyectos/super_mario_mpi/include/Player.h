#ifndef _PLAYER
#define _PLAYER
#include "Mario.h"
class Player {
  private:
    Mario * mario;
    bool active;
  public:
    Player();
    ~Player();
    void setActive(bool);
    bool isActive();
};
#endif
