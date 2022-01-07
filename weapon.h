#ifndef WEAPON_H
#define WEAPON_H

#include "gameobject.h"

class Weapon : public GameObject
{
public:
    Weapon();

    void setType(int type);

    void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection);

};

#endif // WEAPON_H
