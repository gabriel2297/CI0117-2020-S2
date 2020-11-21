#ifndef _WORLD
#define _WORLD
#include <queue>
typedef int Enemy;

class World {
  private:
    queue<* World> cola;
    queue * array;
    int coin;
    int hole;
    Enemy litle_goomba;
    Enemy koopa_troopa;
    int flag;
  public:
    World();
    ~World();
    void setCoin(int); //Coloca una moneda en una posicion x
    void setHole(int); //Coloca un agujero en una posicion x
    void setLittle_Goomba(int); //Asigna un little_goomba a una posicion x
    void setKoopa_troopa(int); //Asigna un koopa_troopa a una posicion x
    bool thereIsaCoin(int); //Si hay una moneda en x posicion
    bool thereIsaHole(int); //Si hay un agujero en x posicion
    bool thereIsaEnemy(int); //Si hay un enemigo en x posicion
};
#endif
