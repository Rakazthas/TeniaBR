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

    virtual void setType(int type);

    void handleCollision(GameObject *collider);

    virtual bool needDestroy();

    virtual void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection);

private:
    int damage;
    float dmgRadius;
    bool boom = false;


};

#endif // PROJECTILE_H
