#include "projectile.h"

Projectile::Projectile()
{

}

int Projectile::getDamage(){return damage;}
int Projectile::getDmgRadius(){return dmgRadius;}

void Projectile::setDamage(int newDmg){
    damage = newDmg;
}
void Projectile::setDmgRadius(int newRadius){
    dmgRadius = newRadius;
}

void Projectile::setType(int type){
    if(type<4)
        category = 4;
    else if(type>6)
        category = 6;
    else
        category = type;
}
