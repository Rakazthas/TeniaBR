#ifndef WORM_H
#define WORM_H

#include "gameobject.h"


class Worm : public GameObject
{
public:
    Worm();
    Worm(Transform transform);

    int getHp();
    void setHp(int newHP);

    virtual bool needDestroy();


    virtual void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection);

private:
    int hp;
};

#endif // WORM_H
