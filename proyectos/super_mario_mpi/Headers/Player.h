#ifndef _PLAYER
#define _PLAYER
class Player {
  private:
    int coins;
    bool active;
    int strategy;
  public:
    Player(int);
    ~Player();
    bool setActive(bool);
    int getStrategy(int);
    void attack(int);
};
#endif
