#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <Qt3DRender/QMesh>
#include <QOpenGLShaderProgram>

#include "transform.h"

class GameObject
{
public:
    GameObject();


    //getter
    GameObject* getParent();
    std::vector<GameObject*> getChildren();
    Transform getTransform();
    std::vector<QVector3D> getVertices();
    std::vector<std::vector<int>> getFaces();
    float getWeight();
    float getElasticity();
    bool testLink();
    QVector2D getPos();

    //setter
    void setParent(GameObject* newParent);
    void setChildren(std::vector<GameObject*> newChildren);
    void addChild(GameObject* child);
    void removeChild(GameObject* child);
    void setTransform(Transform newTransform);
    void setVertices(std::vector<QVector3D> newVertices);
    void setFaces(std::vector<std::vector<int>> newFaces);
    void setWeight(float newWeight);
    void setElasticity(float newElasticity);
    void setLink(bool link = true);
    void setPos(QVector2D newPos);



    void render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, /*GeometryEngine *geometries,*/ QMatrix4x4 projection);
    void updateTransform();

protected:
    float weight;
    float elasticity;
    bool isLink = false;

    QVector2D position;

    GameObject* parent;

    Transform transform;

    std::vector<QVector3D> vertices;
    std::vector<std::vector<int>> faces;



    std::vector<GameObject*> children;
};

#endif // GAMEOBJECT_H
