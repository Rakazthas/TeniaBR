#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"

class Projectile : public GameObject
{
public:
    Projectile();

    int getDamage();
    int getDmgRadius();

    void setDamage(int newDmg);
    void setDmgRadius(int newRadius);

    void setType(int type);

private:
    int damage;
    int dmgRadius;


};

#endif // PROJECTILE_H
