#include "gameobject.h"

GameObject::GameObject()
{
    parent = nullptr;
    children = std::vector<GameObject*>();
    transform = Transform();


}

GameObject* GameObject::getParent(){return parent;}
std::vector<GameObject*> GameObject::getChildren(){return children;}
Transform GameObject::getTransform(){return transform;}
float GameObject::getWeight(){return weight;}
float GameObject::getElasticity(){return elasticity;}
bool GameObject::testLink(){return isLink;}
QVector2D GameObject::getPos(){return worldPosition;}


void GameObject::setParent(GameObject *newParent){
    parent = newParent;
}
void GameObject::setChildren(std::vector<GameObject *> newChildren){
    children = newChildren;
}
void GameObject::addChild(GameObject *child){
    children.push_back(child);
}
void GameObject::removeChild(GameObject *child){
    child->setParent(NULL);
    std::vector<GameObject*>::iterator pos = std::find(children.begin(), children.end(), child);
    if(pos != children.end())
        children.erase(pos);
}

void GameObject::setTransform(Transform newTransform){
    transform = newTransform;
}

void GameObject::setWeight(float newWeight){
    weight = newWeight;
}
void GameObject::setElasticity(float newElasticity){
    elasticity = newElasticity;
}
void GameObject::setLink(bool link){
    isLink = link;
}
void GameObject::setPos(QVector2D newPos){
    worldPosition = newPos;
}

void GameObject::getBoundingBox(QVector2D *upRight, QVector2D *downLeft){
    *upRight = AABB[1];
    *downLeft = AABB[0];
}

void GameObject::updateBoundingBox(){
    QMatrix4x4 worldTransform = getWorldTransform();

    worldPosition = QVector2D(worldTransform(0,3), worldTransform(1,3));
    float scaleX = worldTransform.column(0).length();
    float scaleY = worldTransform.column(1).length();
    worldScale = QVector2D(scaleX, scaleY);
    worldRotationAxis = std::acos(worldTransform(0,0)); //a verif

    float tempx[4], tempy[4], x[4], y[4];
    tempx[0] = -width*scaleX; tempx[1] = width*scaleX; tempx[2] = -width*scaleX; tempx[3] = width*scaleX;
    tempy[0] = height*scaleY; tempy[1] = height*scaleY; tempy[2] = -height*scaleY; tempy[3] = -height*scaleY;

    for(unsigned int i = 0; i < 4; i++){
        x[i] = tempx[i]*std::cos(worldRotationAxis) - tempy[i]*std::sin(worldRotationAxis);
        y[i] = tempx[i]*std::sin(worldRotationAxis) + tempy[i]*std::cos(worldRotationAxis);

        x[i] += worldPosition.x();
        y[i] += worldPosition.y();
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();

    for(unsigned int i = 0; i < 4; i++){
        if(x[i] < minX)
            minX = x[i];
        if(x[i] > maxX)
            maxX = x[i];
        if(y[i] < minY)
            minY = y[i];
        if(y[i] > maxY)
            maxY = y[i];
    }

    AABB[0] = QVector2D(minX, minY);
    AABB[1] = QVector2D(maxX, maxY);
}

void GameObject::updateBoundingBox(QMatrix4x4 worldTransform){
    worldPosition = QVector2D(worldTransform(0,3), worldTransform(1,3));
    float scaleX = worldTransform.column(0).length();
    float scaleY = worldTransform.column(1).length();
    worldScale = QVector2D(scaleX, scaleY);
    worldRotationAxis = std::acos(worldTransform(0,0)); //a verif

    float tempx[4], tempy[4], x[4], y[4];
    tempx[0] = -width*scaleX; tempx[1] = width*scaleX; tempx[2] = -width*scaleX; tempx[3] = width*scaleX;
    tempy[0] = height*scaleY; tempy[1] = height*scaleY; tempy[2] = -height*scaleY; tempy[3] = -height*scaleY;

    for(unsigned int i = 0; i < 4; i++){
        x[i] = tempx[i]*std::cos(worldRotationAxis) - tempy[i]*std::sin(worldRotationAxis);
        y[i] = tempx[i]*std::sin(worldRotationAxis) + tempy[i]*std::cos(worldRotationAxis);

        x[i] += worldPosition.x();
        y[i] += worldPosition.y();
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();

    for(unsigned int i = 0; i < 4; i++){
        if(x[i] < minX)
            minX = x[i];
        if(x[i] > maxX)
            maxX = x[i];
        if(y[i] < minY)
            minY = y[i];
        if(y[i] > maxY)
            maxY = y[i];
    }

    AABB[0] = QVector2D(minX, minY);
    AABB[1] = QVector2D(maxX, maxY);
}


QMatrix4x4 GameObject::getWorldTransform(){
    if(parent == nullptr){
        return transform.getTransform();
    }else{
        return parent->getWorldTransform()*transform.getTransform();
    }
}


void GameObject::render(QMatrix4x4 globalTransform, QOpenGLShaderProgram* program, QMatrix4x4 projection){
    QMatrix4x4 newTransform = globalTransform * transform.getTransform();
    program->setUniformValue("mvp_matrix", projection * newTransform);


    for(unsigned int i = 0; i < children.size(); i++){
        children[i]->render(newTransform, program, projection);
    }
}
