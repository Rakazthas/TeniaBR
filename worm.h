#ifndef WORM_H
#define WORM_H

#include "gameobject.h"

class Worm : public GameObject
{
public:
    Worm();

    int getHp();

    void setHp(int newHP);

private:
    int hp;
};

#endif // WORM_H
