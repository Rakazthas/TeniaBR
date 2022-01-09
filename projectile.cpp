#include "projectile.h"

Projectile::Projectile()
{
    category = 4;

    weight = 0;
    elasticity = 0;

    transform = Transform();



    height = 0;
    width =0 ;//TODO update when sprite ok

    updateBoundingBox();

    damage = 3;
    dmgRadius = 1.5f;
}

Projectile::Projectile(Transform transform){
    category = 4;

    weight = 0;
    elasticity = 0;

    this->transform = transform;



    height = 0;
    width =0 ;//TODO update when sprite ok

    updateBoundingBox();

    damage = 3;
    dmgRadius = 1.5f;
}

int Projectile::getDamage(){return damage;}
float Projectile::getDmgRadius(){return dmgRadius;}

void Projectile::setDamage(int newDmg){
    damage = newDmg;
}
void Projectile::setDmgRadius(float newRadius){
    dmgRadius = newRadius;
}

void Projectile::setType(int type){
    if(type<4)
        category = 4;
    else if(type>6)
        category = 6;
    else
        category = type;

    //TODO update size/box/dmg
}
