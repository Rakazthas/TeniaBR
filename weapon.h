#ifndef WEAPON_H
#define WEAPON_H

#include "gameobject.h"


class Weapon : public GameObject
{
public:
    Weapon();
    Weapon(Transform transform);

    void setType(int type);

    virtual void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection);

};

#endif // WEAPON_H
