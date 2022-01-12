#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <Qt3DRender/QMesh>
#include <QOpenGLShaderProgram>
#include <cmath>

#include "transform.h"
#include "geometryengine.h"


class GameObject
{
public:
    GameObject();


    //getter
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    Transform getTransform();
    float getWeight();
    float getElasticity();
    bool testLink();
    QVector2D getPos();
    QVector2D getMovement();
    float getHeight();
    float getWidth();

    //setter
    void setParent(GameObject* newParent);
    void setChildren(std::vector<GameObject*> newChildren);
    void addChild(GameObject* child);
    void removeChild(GameObject* child);
    void setTransform(Transform newTransform);
    void setWeight(float newWeight);
    void setElasticity(float newElasticity);
    void setLink(bool link = true);
    void setPos(QVector2D newPos);

    void getBoundingBox(QVector2D *upRight, QVector2D *downLeft);
    void updateBoundingBox();
    void updateBoundingBox(QMatrix4x4 worldTransform);

    void setMovement(QVector2D move);

    QMatrix4x4 getWorldTransform();


    void applyMovement(float time);
    void handleCollision(GameObject *collider);

    virtual bool needDestroy();
    virtual void setType(int type);


    virtual void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection);
    void updateTransform();

protected:
    float weight;
    float elasticity;
    bool isLink = false;

    QVector2D worldPosition;
    QVector2D worldScale; //devrait rester 1 ?
    float worldRotationAxis;
    float height;
    float width;
    QVector2D AABB[2];

    GameObject* parent;

    Transform transform;
    QVector2D movement;

    int category;

    std::vector<GameObject*> children;
};

#endif // GAMEOBJECT_H
