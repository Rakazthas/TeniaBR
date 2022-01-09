#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"


class Projectile : public GameObject
{
public:
    Projectile();
    Projectile(Transform transform);

    int getDamage();
    float getDmgRadius();

    void setDamage(int newDmg);
    void setDmgRadius(float newRadius);

    void setType(int type);

private:
    int damage;
    float dmgRadius;


};

#endif // PROJECTILE_H
