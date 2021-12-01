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
